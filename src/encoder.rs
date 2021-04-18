use audiopus::{coder::Encoder, Application, Bitrate, Channels, SampleRate, TryFrom};
use ext_php_rs::{
    parse_args,
    php::{
        args::Arg,
        class::{ClassBuilder, ClassEntry},
        enums::DataType,
        exceptions,
        execution_data::ExecutionData,
        flags::MethodFlags,
        function::FunctionBuilder,
        types::{long::ZendLong, object::ZendClassObject, zval::Zval},
    },
    ZendObjectHandler,
};

#[derive(Default, Debug, ZendObjectHandler)]
pub struct OpusEncoder {
    encoder: Option<Encoder>,
    sample_rate: ZendLong,
    channels: ZendLong,
}

impl OpusEncoder {
    /// Builds the class object to be called in the module startup function.
    pub fn build_class_object() {
        let constructor = FunctionBuilder::constructor(OpusEncoder::constructor)
            .arg(Arg::new("sample_rate", DataType::Long))
            .arg(Arg::new("channels", DataType::Long))
            .arg(Arg::new("application", DataType::String))
            .build();

        let encode = FunctionBuilder::new("encode", OpusEncoder::encode)
            .arg(Arg::new("data", DataType::Array))
            .arg(Arg::new("frame_size", DataType::Long))
            .returns(DataType::Array, false, false)
            .build();

        let set_bitrate = FunctionBuilder::new("setBitrate", OpusEncoder::set_bitrate)
            .arg(Arg::new("bitrate", DataType::Long))
            .build();

        ClassBuilder::new("OpusEncoder")
            .method(constructor, MethodFlags::Public)
            .method(encode, MethodFlags::Public)
            .method(set_bitrate, MethodFlags::Public)
            .object_override::<OpusEncoder>()
            .build();
    }

    /// The constructor for the encoder.
    pub extern "C" fn constructor(execute_data: &mut ExecutionData, _: &mut Zval) {
        let mut sample_rate = Arg::new("sample_rate", DataType::Long);
        let mut channels = Arg::new("channels", DataType::Long);
        let mut application = Arg::new("application", DataType::Long);

        parse_args!(execute_data, sample_rate, channels, application);

        let sample_rate = match SampleRate::try_from(sample_rate.val::<ZendLong>().unwrap() as _) {
            Ok(x) => x,
            Err(_) => {
                exceptions::throw(
                    ClassEntry::parse_error(),
                    "Invalid sample rate. Must be one of 8000, 12000, 16000, 24000, 48000.",
                );
                return;
            }
        };
        let channels = match Channels::try_from(channels.val::<ZendLong>().unwrap() as _) {
            Ok(x) => x,
            Err(_) => {
                exceptions::throw(
                    ClassEntry::parse_error(),
                    "Invalid channels. Must be one of 1, 2.",
                );
                return;
            }
        };
        let application = match Application::try_from(application.val::<ZendLong>().unwrap() as _) {
            Ok(x) => x,
            Err(_) => {
                exceptions::throw(ClassEntry::parse_error(), "Invalid application. Must be one of `OPUS_APPLICATION_VOIP`, `OPUS_APPLICATION_AUDIO` or `OPUS_APPLICATION_RESTRICTED_LOWDELAY`.");
                return;
            }
        };

        let this = ZendClassObject::<Self>::get(execute_data).unwrap();
        let encoder = Encoder::new(sample_rate, channels, application).unwrap();
        this.encoder = Some(encoder);
        this.sample_rate = sample_rate as _;
        this.channels = channels as _;
    }

    pub extern "C" fn set_bitrate(execute_data: &mut ExecutionData, _: &mut Zval) {
        let mut bitrate = Arg::new("bitrate", DataType::Long);
        parse_args!(execute_data, bitrate);

        let bitrate = match Bitrate::try_from(bitrate.val::<ZendLong>().unwrap() as _) {
            Ok(x) => x,
            Err(_) => {
                exceptions::throw(ClassEntry::parse_error(), "Invalid bitrate given.");
                return;
            }
        };

        let this = ZendClassObject::<Self>::get(execute_data).unwrap();

        if let Err(e) = this.encoder.as_mut().unwrap().set_bitrate(bitrate) {
            exceptions::throw(
                ClassEntry::error_exception(),
                format!(
                    "Error setting the bitrate of the encoder: {}",
                    e.to_string()
                )
                .as_str(),
            )
        }
    }

    /// Encodes an array of Opus data.
    pub extern "C" fn encode(execute_data: &mut ExecutionData, retval: &mut Zval) {
        let mut data = Arg::new("data", DataType::Array);
        let mut frame_size = Arg::new("frame_size", DataType::Long);
        parse_args!(execute_data, data, frame_size);

        let this = ZendClassObject::<Self>::get(execute_data).unwrap();
        let arr = data.zval().unwrap().array().unwrap();
        let pcm: Vec<ZendLong> = (&arr).into();
        let mut output =
            Vec::with_capacity((frame_size.val::<ZendLong>().unwrap() * this.channels * 2) as _);

        let result = this
            .encoder
            .as_ref()
            .unwrap()
            .encode(&[1, 2, 3, 4], &mut output);

        if result.is_err() {
            let err = result.unwrap_err().to_string();
            exceptions::throw(
                ClassEntry::error_exception(),
                format!("Error encoding PCM to Opus: {}", err).as_str(),
            );
            return;
        }

        retval.set_array(output);
    }
}
