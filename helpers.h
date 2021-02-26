#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdint.h>

static const char* invalid_sample_rate_error = "sample rate must be one of [8000, 12000, 16000, 24000, 48000], got %ld";
static const char* invalid_channel_error = "channels must be one of [1, 2], got %ld";
static const char* invalid_application_error = "application must be one of [OPUS_APPLICATION_VOIP, OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_LOWDELAY], got %ld";
static const char* invalid_bandwidth_error = "bandwidth must be one of [OPUS_AUTO, OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND, OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND], got %ld";
static const char* invalid_bitrate_error = "bitrate must be one of [OPUS_AUTO, OPUS_BITRATE_MAX] or between 500 and 512,000 incluside, got %ld";
static const char* invalid_frame_size_error = "frame size must be one of [OPUS_FRAMESIZE_ARG, OPUS_FRAMESIZE_2_5_MS, OPUS_FRAMESIZE_5_MS, OPUS_FRAMESIZE_10_MS, OPUS_FRAMESIZE_20_MS, OPUS_FRAMESIZE_40_MS, OPUS_FRAMESIZE_60_MS, OPUS_FRAMESIZE_80_MS, OPUS_FRAMESIZE_100_MS, OPUS_FRAMESIZE_120_MS], got %ld";

int validate_sample_rate(int32_t sample_rate);
int validate_channels(int8_t channels);
int validate_application(int32_t application);
int validate_bandwidth(int32_t bandwidth);
int validate_bitrate(int32_t bitrate);
int validate_framesize(int32_t frame_size);

#endif