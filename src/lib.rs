use std::convert::TryFrom;

use anyhow::{bail, Context, Result};
use audiopus::{coder::Encoder, Application, Bitrate, Channels, SampleRate};
use ext_php_rs::prelude::*;

/// Encodes 16-bit PCM audio data into Opus frames.
#[php_class]
#[derive(Debug)]
pub struct OpusEncoder {
    encoder: Encoder,
}

#[php_const]
const OPUS_APPLICATION_VOIP: i32 = Application::Voip as i32;
#[php_const]
const OPUS_APPLICATION_AUDIO: i32 = Application::Audio as i32;
#[php_const]
const OPUS_APPLICATION_LOW_DELAY: i32 = Application::LowDelay as i32;

#[php_impl]
impl OpusEncoder {
    /// Creates a new opus encoder.
    ///
    /// @param int $sample_rate Sample rate of the encoder.
    /// @param int $channels Number of channels of the encoder.
    /// @param int $application Application used by the encoder.
    ///
    /// @return OpusEncoder
    pub fn __construct(sample_rate: i32, channels: i32, application: i32) -> Result<Self> {
        let sample_rate = SampleRate::try_from(sample_rate)
            .context("Invalid value given for sample rate. Must be in Hz, one of 8000, 12000, 16000, 24000, 48000")?;
        let channels = match channels {
            1 => Channels::Mono,
            2 => Channels::Stereo,
            _ => bail!("Invalid value given for channels. Must be 1 or 2"),
        };
        let application = Application::try_from(application)
            .context("Invalid value given for application. Must be one of `OPUS_APPLICATION_VOIP`, `OPUS_APPLICATION_AUDIO` or `OPUS_APPLICATION_LOW_DELAY`")?;

        Ok(Self {
            encoder: Encoder::new(sample_rate, channels, application)
                .context("Failed to create Opus encoder")?,
        })
    }

    /// Sets the bitrate of the Opus encoder.
    ///
    /// @param int $bitrate Bitrate of the encoder.
    pub fn set_bitrate(&mut self, bitrate: i32) -> Result<()> {
        let bitrate =
            Bitrate::try_from(bitrate).with_context(|| "Invalid value given for bitrate")?;
        self.encoder
            .set_bitrate(bitrate)
            .with_context(|| "Failed to set bitrate of encoder")
    }

    /// Encodes 16-bit PCM into an Opus frame.
    ///
    /// If the encoder is set up for dual channels, the input must be interleaved.
    ///
    /// @param int[] $input Input 16-bit PCM frame.
    ///
    /// @return int[]
    pub fn encode(&mut self, input: Vec<i16>) -> Result<Vec<u8>> {
        let mut output = vec![0; input.len() * 2];
        let len = self.encoder.encode(&input, &mut output)?;
        output.truncate(len);
        Ok(output)
    }
}

/// Retrieves the version of Opus that `opus-php` is using.
///
/// @return string
#[php_function]
pub fn opus_version() -> String {
    audiopus::version().into()
}

#[php_module]
pub fn get_module(module: ModuleBuilder) -> ModuleBuilder {
    module
}
