#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdint.h>
#include "php.h"
#include "zend_exceptions.h"

#define THROW(code, msg, args...) \
	zend_throw_exception_ex(opus_exception_ce, code, msg, args); \
	return;

#define CTOP_CONST(c) \
	CTOP_CONST_EX(c, #c);

#define CTOP_CONST_EX(c, alias) \
	REGISTER_LONG_CONSTANT(alias, c, CONST_CS | CONST_PERSISTENT);

#define HANDLE_OPUS_ERR(e, msg) \
	if (e != OPUS_OK) { \
		zend_throw_exception_ex(opus_exception_ce, e, "%s: %s", msg, opus_strerror(e)); \
		return; \
	}

extern zend_class_entry *opus_exception_ce;

extern const char* invalid_sample_rate_error;
extern const char* invalid_channel_error;
extern const char* invalid_application_error;
extern const char* invalid_bandwidth_error;
extern const char* invalid_bitrate_error;
extern const char* invalid_frame_size_error;

int validate_sample_rate(int32_t sample_rate);
int validate_channels(int8_t channels);
int validate_application(int32_t application);
int validate_bandwidth(int32_t bandwidth);
int validate_bitrate(int32_t bitrate);
int validate_framesize(int32_t frame_size);

#endif