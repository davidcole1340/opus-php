/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 0544da712e6c275a02eb1c1458d242abd11001cc */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_opus_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OpusEncoder___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, sample_rate, IS_LONG, 0, "48000")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channels, IS_LONG, 0, "2")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, application, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()


ZEND_FUNCTION(opus_version);
ZEND_METHOD(OpusEncoder, __construct);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(opus_version, arginfo_opus_version)
	ZEND_FE_END
};


static const zend_function_entry class_OpusEncoder_methods[] = {
	ZEND_ME(OpusEncoder, __construct, arginfo_class_OpusEncoder___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
