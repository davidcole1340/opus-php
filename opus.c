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
#include "encoder.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

zend_object_handlers opus_encoder_object_handlers;
zend_class_entry *opus_encoder_ce;
zend_class_entry *opus_exception_ce;

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
	CTOP_CONST(OPUS_FRAMESIZE_120_MS);

	// register signal constants
	CTOP_CONST(OPUS_SIGNAL_VOICE);
	CTOP_CONST(OPUS_SIGNAL_MUSIC);

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
	ext_functions,			/* zend_function_entry */
	PHP_MINIT(opus),		/* PHP_MINIT - Module initialization */
	NULL,					/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(opus),		/* PHP_RINIT - Request initialization */
	NULL,					/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(opus),		/* PHP_MINFO - Module info */
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
