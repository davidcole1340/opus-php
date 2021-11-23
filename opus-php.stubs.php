<?php

// Stubs for opus-php

namespace {
    const OPUS_APPLICATION_VOIP = null;

    const OPUS_APPLICATION_AUDIO = null;

    const OPUS_APPLICATION_LOW_DELAY = null;

    /**
     * Retrieves the version of Opus that `opus-php` is using.
     *
     * @return string
     */
    function opus_version(): string {}

    /**
     * Encodes 16-bit PCM audio data into Opus frames.
     */
    class OpusEncoder {
        /**
         * Creates a new opus encoder.
         *
         * @param int $sample_rate Sample rate of the encoder.
         * @param int $channels Number of channels of the encoder.
         * @param int $application Application used by the encoder.
         *
         * @return OpusEncoder
         */
        public function __construct(int $sample_rate, int $channels, int $application) {}

        /**
         * Sets the bitrate of the Opus encoder.
         *
         * @param int $bitrate Bitrate of the encoder.
         */
        public function setBitrate(int $bitrate): mixed {}

        /**
         * Encodes 16-bit PCM into an Opus frame.
         *
         * If the encoder is set up for dual channels, the input must be interleaved.
         *
         * @param int[] $input Input 16-bit PCM frame.
         *
         * @return int[]
         */
        public function encode(array $input): array {}
    }
}
