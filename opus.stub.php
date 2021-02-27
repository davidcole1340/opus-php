<?php

/** @generate-function-entries */

/**
 * Returns the version of libopus that the
 * `opus` extension was compiled with.
 *
 * @return string
 */
function opus_version(): string {}

/**
 * Represents an opus encoder.
 * 
 * @author David Cole <david.cole1340@gmail.com>
 */
class OpusEncoder
{
    public function __construct(int $sample_rate = 48000, int $channels = 2, int $application = 0) {}
    public function __destruct() {}

    // START GENERIC CTLS - https://opus-codec.org/docs/opus_api-1.3.1/group__opus__genericctls.html
    public function reset(): void {}
    public function getFinalRange(): int {}
    public function getBandwidth(): int {}
    public function getSampleRate(): int {}
    public function isPhaseInversionEnabled(): bool {}
    public function setPhaseInversion(bool $enabled): void {}
    public function getDtxState(): bool {}
    // END GENERIC CTLS

    // START ENCODER CTLS
    public function getApplication(): int {}
    public function getBitrate(): int {}
    public function getComplexity(): int {}
    public function getFrameDuration(): int {}
    public function getChannelsForced(): int {}
    public function getInbandFEC(): bool {}
    public function getLookahead(): int {}
    public function getLsbDepth(): int {}
    public function getMaxBandwidth(): int {}
    public function getPacketLossPercentage(): int {}
    public function isPredictionEnabled(): bool {}
    public function getSignal(): int {}
    public function getVbr(): int {}
    public function getVbrConstraint(): int {}

    public function setApplication(int $application): void {}
    public function setBandwidth(int $bandwidth): void {}
    public function setBitrate(int $bitrate): void {}
    public function setComplexity(int $complexity): void {}
    public function setDtxState(bool $dtx): void {}
    public function setFrameDuration(int $frameDuration): void {}
    public function setChannelsForced(int $channels): void {}
    public function setInbandFEC(bool $enabled): void {}
    public function setLsbDepth(int $lsb): void {}
    public function setMaxBandwidth(int $maxBandwidth): void {}
    public function setPacketLossPercentage(int $packetLossPercentage): void {}
    public function setPrediction(bool $enabled): void {}
    public function setSignal(int $signal): void {}
    public function setVbrEnabled(bool $enabled): void {}
    public function setVbrConstrained(bool $constrained): void {}
    // END ENCODER CTLS

    // START ENCODER FUNCTIONS
    public function encode(array $pcm): array {}
    // END ENCODER FUNCTIONS
}