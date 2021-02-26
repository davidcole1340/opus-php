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

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

static zend_object_handlers opus_encoder_object_handlers;

#define Z_OPUS_ENCODER_P(zv) \
	((opus_encoder_t*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(opus_encoder_t, std)))

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
	REGISTER_LONG_CONSTANT("OPUS_APPLICATION_VOIP", OPUS_APPLICATION_VOIP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OPUS_APPLICATION_AUDIO", OPUS_APPLICATION_AUDIO, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OPUS_APPLICATION_LOWDELAY", OPUS_APPLICATION_RESTRICTED_LOWDELAY, CONST_CS | CONST_PERSISTENT);

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

	if (sample_rate != 8000 &&
		sample_rate != 12000 &&
		sample_rate != 16000 &&
		sample_rate != 24000 &&
		sample_rate != 48000) {
			zend_throw_exception_ex(opus_exception_ce, -1, "sample rate must be one of [8000, 12000, 16000, 24000, 48000], got %ld", sample_rate);
			return;
		}

	if (channels != 1 &&
		channels != 2) {
			zend_throw_exception_ex(opus_exception_ce, -1, "channels must be one of [1, 2], got %ld", channels);
			return;
		}

	if (application != OPUS_APPLICATION_VOIP &&
		application != OPUS_APPLICATION_AUDIO &&
		application != OPUS_APPLICATION_RESTRICTED_LOWDELAY) {
			zend_throw_exception_ex(opus_exception_ce, -1, "application must be one of [OPUS_APPLICATION_VOIP, OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_LOWDELAY], got %ld", application);
			return;
		}

	encoder = opus_encoder_create((opus_int32)sample_rate, channels, application, &err);

	if (err != OPUS_OK) {
		zend_throw_exception(opus_exception_ce, opus_strerror(err), err);
		return;
	}

	self->encoder = encoder;
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
