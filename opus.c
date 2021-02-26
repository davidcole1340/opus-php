/* opus extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "opus.h"
#include "php.h"
#include "ext/standard/info.h"
#include "php_opus.h"
#include "opus_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_FUNCTION(opus_version)
{
	zend_string *retval;

	retval = strpprintf(0, "%s", opus_get_version_string());

	RETURN_STR(retval);
}
// /* {{{ void test1() */
// PHP_FUNCTION(test1)
// {
// 	ZEND_PARSE_PARAMETERS_NONE();

// 	php_printf("The extension %s is loaded and working!\r\n", "opus");
// }
// /* }}} */

// /* {{{ string test2( [ string $var ] ) */
// PHP_FUNCTION(test2)
// {
// 	char *var = "World";
// 	size_t var_len = sizeof("World") - 1;
// 	zend_string *retval;

// 	ZEND_PARSE_PARAMETERS_START(0, 1)
// 		Z_PARAM_OPTIONAL
// 		Z_PARAM_STRING(var, var_len)
// 	ZEND_PARSE_PARAMETERS_END();

// 	retval = strpprintf(0, "Hello %s", var);

// 	RETURN_STR(retval);
// }
// /* }}}*/

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
	NULL,							/* PHP_MINIT - Module initialization */
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
