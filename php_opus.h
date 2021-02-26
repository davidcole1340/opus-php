/* opus extension for PHP */

#ifndef PHP_OPUS_H
# define PHP_OPUS_H

extern zend_module_entry opus_module_entry;
# define phpext_opus_ptr &opus_module_entry

# define PHP_OPUS_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_OPUS)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_OPUS_H */
