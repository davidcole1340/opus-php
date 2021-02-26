#include "helpers.h"
#include "opus.h"

const char* invalid_sample_rate_error = "sample rate must be one of [8000, 12000, 16000, 24000, 48000], got %ld";
const char* invalid_channel_error = "channels must be one of [1, 2], got %ld";
const char* invalid_application_error = "application must be one of [OPUS_APPLICATION_VOIP, OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_LOWDELAY], got %ld";
const char* invalid_bandwidth_error = "bandwidth must be one of [OPUS_AUTO, OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND, OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND], got %ld";
const char* invalid_max_bandwidth_error = "max bandwidth must be one of [OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND, OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND], got %ld";
const char* invalid_bitrate_error = "bitrate must be one of [OPUS_AUTO, OPUS_BITRATE_MAX] or between 500 and 512,000 incluside, got %ld";
const char* invalid_frame_size_error = "frame size must be one of [OPUS_FRAMESIZE_ARG, OPUS_FRAMESIZE_2_5_MS, OPUS_FRAMESIZE_5_MS, OPUS_FRAMESIZE_10_MS, OPUS_FRAMESIZE_20_MS, OPUS_FRAMESIZE_40_MS, OPUS_FRAMESIZE_60_MS, OPUS_FRAMESIZE_80_MS, OPUS_FRAMESIZE_100_MS, OPUS_FRAMESIZE_120_MS], got %ld";
const char* invalid_signal_error = "signal must be one of [OPUS_AUTO, OPUS_SIGNAL_VOICE, OPUS_SIGNAL_MUSIC], got %ld";

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

int validate_bandwidth(int32_t bandwidth, uint8_t opus_auto)
{
    return (bandwidth == OPUS_AUTO && opus_auto) ||
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

int validate_signal(int32_t signal)
{
    return signal == OPUS_AUTO ||
        signal == OPUS_SIGNAL_VOICE ||
        signal == OPUS_SIGNAL_MUSIC;
}