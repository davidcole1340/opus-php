#include "helpers.h"
#include "opus.h"

int validate_sample_rate(int32_t sample_rate)
{
    return sample_rate == 8000 ||
        sample_rate == 12000 ||
        sample_rate == 16000 ||
        sample_rate == 24000 ||
        sample_rate == 48000;
}

int validate_channels(int8_t channels)
{
    return channels == 1 || channels == 2;
}

int validate_application(int32_t application)
{
    return application == OPUS_APPLICATION_AUDIO ||
        application == OPUS_APPLICATION_RESTRICTED_LOWDELAY ||
        application == OPUS_APPLICATION_VOIP;
}

int validate_bandwidth(int32_t bandwidth)
{
    return bandwidth == OPUS_AUTO ||
        bandwidth == OPUS_BANDWIDTH_FULLBAND ||
        bandwidth == OPUS_BANDWIDTH_MEDIUMBAND ||
        bandwidth == OPUS_BANDWIDTH_NARROWBAND ||
        bandwidth == OPUS_BANDWIDTH_WIDEBAND ||
        bandwidth == OPUS_BANDWIDTH_SUPERWIDEBAND;
}

int validate_bitrate(int32_t bitrate)
{
    return bitrate == OPUS_AUTO ||
        bitrate == OPUS_BITRATE_MAX ||
        (bitrate >= 500 && bitrate <= 512000);
}

int validate_framesize(int32_t frame_size)
{
    return frame_size == OPUS_FRAMESIZE_ARG ||
        frame_size == OPUS_FRAMESIZE_2_5_MS ||
        frame_size == OPUS_FRAMESIZE_5_MS ||
        frame_size == OPUS_FRAMESIZE_10_MS ||
        frame_size == OPUS_FRAMESIZE_20_MS ||
        frame_size == OPUS_FRAMESIZE_40_MS ||
        frame_size == OPUS_FRAMESIZE_60_MS ||
        frame_size == OPUS_FRAMESIZE_80_MS ||
        frame_size == OPUS_FRAMESIZE_100_MS ||
        frame_size == OPUS_FRAMESIZE_120_MS;
}