<?php

/** @generate-function-entries */

/**
 * Returns the version of libopus that the
 * `opus` extension was compiled with.
 *
 * @return string
 */
function opus_version(): string
{
}

/**
 * Represents an opus encoder.
 * 
 * @author David Cole <david.cole1340@gmail.com>
 */
class OpusEncoder
{
    public function __construct(int $sample_rate = 48000, int $channels = 2, int $application = 0)
    {
    }
}