/* opus extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "opus.h"
#include "php.h"
#include "zend_exceptions.h"
#include "ext/standard/info.h"
#include "php_opus.h"
#include "opus_arginfo.h"
#include "helpers.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

static zend_object_handlers opus_encoder_object_handlers;

#define Z_OPUS_ENCODER_P(zv) \
	((opus_encoder_t*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(opus_encoder_t, std)))

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

zend_object *opus_encoder_new(zend_class_entry *ce)
{
	opus_encoder_t *encoder = zend_object_alloc(sizeof(opus_encoder_t), ce);

	zend_object_std_init(&encoder->std, ce);
	encoder->std.handlers = &opus_encoder_object_handlers;
	return &encoder->std;
}

static zend_class_entry *opus_exception_ce;
static zend_class_entry *opus_encoder_ce;

PHP_MINIT_FUNCTION(opus)
{
	zend_class_entry ce;

	// register application type constants
	CTOP_CONST(OPUS_APPLICATION_VOIP);
	CTOP_CONST(OPUS_APPLICATION_AUDIO);
	CTOP_CONST_EX(OPUS_APPLICATION_RESTRICTED_LOWDELAY, "OPUS_APPLICATION_LOWDELAY");
	
	// register bandwidth type constants
	CTOP_CONST(OPUS_AUTO);
	CTOP_CONST(OPUS_BANDWIDTH_NARROWBAND);
	CTOP_CONST(OPUS_BANDWIDTH_MEDIUMBAND);
	CTOP_CONST(OPUS_BANDWIDTH_WIDEBAND);
	CTOP_CONST(OPUS_BANDWIDTH_SUPERWIDEBAND);
	CTOP_CONST(OPUS_BANDWIDTH_FULLBAND);

	// register framesize constants
	CTOP_CONST(OPUS_FRAMESIZE_ARG);
	CTOP_CONST(OPUS_FRAMESIZE_2_5_MS);
	CTOP_CONST(OPUS_FRAMESIZE_5_MS);
	CTOP_CONST(OPUS_FRAMESIZE_10_MS);
	CTOP_CONST(OPUS_FRAMESIZE_20_MS);
	CTOP_CONST(OPUS_FRAMESIZE_40_MS);
	CTOP_CONST(OPUS_FRAMESIZE_60_MS);
	CTOP_CONST(OPUS_FRAMESIZE_80_MS);
	CTOP_CONST(OPUS_FRAMESIZE_100_MS);
	CTOP_CONST(OPUS_FRAMESIZE_120_MS)

	// register opus exception
	INIT_CLASS_ENTRY(ce, "OpusException", NULL);
	opus_exception_ce = zend_register_internal_class_ex(&ce, zend_exception_get_default());

	// register opus encoder
	INIT_CLASS_ENTRY(ce, "OpusEncoder", class_OpusEncoder_methods);
	opus_encoder_ce = zend_register_internal_class(&ce);
	opus_encoder_ce->create_object = opus_encoder_new;
	memcpy(&opus_encoder_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	opus_encoder_object_handlers.offset = XtOffsetOf(opus_encoder_t, std);

	return SUCCESS;
}

PHP_FUNCTION(opus_version)
{
	zend_string *retval;

	retval = strpprintf(0, "%s", opus_get_version_string());

	RETURN_STR(retval);
}

PHP_METHOD(OpusEncoder, __construct)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	OpusEncoder *encoder;
	int err;
	zend_long sample_rate, channels, application;

	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL Z_PARAM_LONG(sample_rate)
		Z_PARAM_OPTIONAL Z_PARAM_LONG(channels)
		Z_PARAM_OPTIONAL Z_PARAM_LONG(application)
	ZEND_PARSE_PARAMETERS_END();

	if (! validate_sample_rate(sample_rate)) {
		THROW(-1, invalid_sample_rate_error, sample_rate);
	}

	if (! validate_channels(channels)) {
		THROW(-1, invalid_channel_error, channels);
	}

	if (validate_application(application)) {
		THROW(-1, invalid_application_error, application);
	}

	encoder = opus_encoder_create((opus_int32)sample_rate, channels, application, &err);
	HANDLE_OPUS_ERR(err, "could not create new opus encoder");

	self->encoder = encoder;
}

#define OPUS_ENCODER_GET(methodName, resultType, op, returnMacro) \
	PHP_METHOD(OpusEncoder, methodName) \
	{ \
		opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS); \
		resultType result; \
		int err = opus_encoder_ctl(self->encoder, op(&result)); \
		HANDLE_OPUS_ERR(err, "could not methodName"); \
		returnMacro; \
	}

OPUS_ENCODER_GET(getFinalRange, opus_uint32, OPUS_GET_FINAL_RANGE, RETURN_LONG(result));
OPUS_ENCODER_GET(getBandwidth, opus_int32, OPUS_GET_BANDWIDTH, RETURN_LONG(result));
OPUS_ENCODER_GET(getSampleRate, opus_int32, OPUS_GET_SAMPLE_RATE, RETURN_LONG(result));
OPUS_ENCODER_GET(isPhaseInversionEnabled, opus_int32, OPUS_GET_PHASE_INVERSION_DISABLED, RETURN_BOOL(result == 1));
OPUS_ENCODER_GET(getDtxState, opus_int32, OPUS_GET_DTX, RETURN_BOOL(result == 1));
OPUS_ENCODER_GET(getApplication, opus_int32, OPUS_GET_APPLICATION, RETURN_LONG(result));
OPUS_ENCODER_GET(getBitrate, opus_int32, OPUS_GET_BITRATE, RETURN_LONG(result));
OPUS_ENCODER_GET(getComplexity, opus_int32, OPUS_GET_COMPLEXITY, RETURN_LONG(result));
OPUS_ENCODER_GET(getFrameDuration, opus_int32, OPUS_GET_EXPERT_FRAME_DURATION, RETURN_LONG(result));
OPUS_ENCODER_GET(getChannelsForced, opus_int32, OPUS_GET_FORCE_CHANNELS, RETURN_LONG(result));
OPUS_ENCODER_GET(getInbandFEC, opus_int32, OPUS_GET_INBAND_FEC, RETURN_BOOL(result == 1));
OPUS_ENCODER_GET(getLookahead, opus_int32, OPUS_GET_LOOKAHEAD, RETURN_LONG(result));
OPUS_ENCODER_GET(getLsbDepth, opus_int32, OPUS_GET_LSB_DEPTH, RETURN_LONG(result));
OPUS_ENCODER_GET(getMaxBandwidth, opus_int32, OPUS_GET_MAX_BANDWIDTH, RETURN_LONG(result));
OPUS_ENCODER_GET(getPacketLossPercentage, opus_int32, OPUS_GET_PACKET_LOSS_PERC, RETURN_LONG(result));
OPUS_ENCODER_GET(isPredictionEnabled, opus_int32, OPUS_GET_PREDICTION_DISABLED, RETURN_BOOL(result == 1));
OPUS_ENCODER_GET(getSignal, opus_int32, OPUS_GET_SIGNAL, RETURN_LONG(result));
OPUS_ENCODER_GET(getVbr, opus_int32, OPUS_GET_VBR, RETURN_LONG(result));
OPUS_ENCODER_GET(getVbrConstraint, opus_int32, OPUS_GET_VBR_CONSTRAINT, RETURN_LONG(result));

PHP_METHOD(OpusEncoder, reset)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);

	int err = opus_encoder_ctl(self->encoder, OPUS_RESET_STATE);
	HANDLE_OPUS_ERR(err, "could not reset encoder");
}

PHP_METHOD(OpusEncoder, setPhaseInversion)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_bool enabled;
	int err;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();

	err = opus_encoder_ctl(self->encoder, OPUS_SET_PHASE_INVERSION_DISABLED(enabled ? 0 : 1));
	HANDLE_OPUS_ERR(err, "could not set phase inversion state");
}

PHP_METHOD(OpusEncoder, setApplication)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long application;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(application)
	ZEND_PARSE_PARAMETERS_END();

	if (! validate_application(application)) {
		THROW(0, invalid_application_error, application);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_APPLICATION(application));
	HANDLE_OPUS_ERR(err, "could not set application");
}

PHP_METHOD(OpusEncoder, setBandwidth)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long bandwidth;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(bandwidth)
	ZEND_PARSE_PARAMETERS_END();

	if (! validate_bandwidth(bandwidth)) {
		THROW(0, invalid_bandwidth_error, bandwidth);
	}
	
	int err = opus_encoder_ctl(self->encoder, OPUS_SET_BANDWIDTH(bandwidth));
	HANDLE_OPUS_ERR(err, "could not set bandwidth");
}

PHP_METHOD(OpusEncoder, setBitrate)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long bitrate;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(bitrate)
	ZEND_PARSE_PARAMETERS_END();
	
	if (! validate_bitrate(bitrate)) {
		THROW(0, invalid_bitrate_error, bitrate);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_BITRATE(bitrate));
	HANDLE_OPUS_ERR(err, "could not set bitrate");
}

PHP_METHOD(OpusEncoder, setComplexity)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long complexity;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(complexity)
	ZEND_PARSE_PARAMETERS_END();
	
	if (complexity < 0 || complexity > 10) {
		THROW(0, "complexity must be between 0 and 10 inclusive, got %ld", complexity);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_COMPLEXITY(complexity));
	HANDLE_OPUS_ERR(err, "could not set complexity");
}

PHP_METHOD(OpusEncoder, setDtxState)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_bool state;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(state)
	ZEND_PARSE_PARAMETERS_END();

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_DTX(state ? 1 : 0));
	HANDLE_OPUS_ERR(err, "could not set dtx state");
}

PHP_METHOD(OpusEncoder, setFrameDuration)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long frameDuration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(frameDuration)		
	ZEND_PARSE_PARAMETERS_END();

	if (! validate_framesize(frameDuration)) {
		THROW(0, invalid_frame_size_error, frameDuration);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_EXPERT_FRAME_DURATION(frameDuration));
	HANDLE_OPUS_ERR(err, "could not set frame duration");
}

PHP_METHOD(OpusEncoder, setChannelsForced)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long channels;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(channels)
	ZEND_PARSE_PARAMETERS_END();
	
	if (channels != OPUS_AUTO && channels != 1 && channels != 2) {
		THROW(0, "channels must be one of [OPUS_AUTO, 1, 2], got %ld", channels);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_FORCE_CHANNELS(channels));
	HANDLE_OPUS_ERR(err, "could not set forced channels");
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(opus)
{
#if defined(ZTS) && defined(COMPILE_DL_OPUS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(opus)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "opus support", "enabled");
	php_info_print_table_row(2, "libopus version", opus_get_version_string());
	php_info_print_table_end();
}
/* }}} */

/* {{{ opus_module_entry */
zend_module_entry opus_module_entry = {
	STANDARD_MODULE_HEADER,
	"opus",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(opus),							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(opus),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(opus),			/* PHP_MINFO - Module info */
	PHP_OPUS_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OPUS
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(opus)
#endif
