use audiopus::{coder::Encoder, Application, Channels, SampleRate, TryFrom};
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
}

impl OpusEncoder {
    /// Builds the class object to be called in the module startup function.
    pub fn build_class_object() {
        let constructor = FunctionBuilder::constructor(OpusEncoder::constructor)
            .arg(Arg::new("sample_rate", DataType::Long))
            .arg(Arg::new("channels", DataType::Long))
            .arg(Arg::new("application", DataType::String))
            .build();

        ClassBuilder::new("OpusEncoder")
            .method(constructor, MethodFlags::Public)
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
    }
}
