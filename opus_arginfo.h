/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 149c85609c59ff3fc928f9f5bd75241c0712d189 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_opus_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OpusEncoder___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, sample_rate, IS_LONG, 0, "48000")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channels, IS_LONG, 0, "2")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, application, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OpusEncoder___destruct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_reset, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_getFinalRange, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpusEncoder_getBandwidth arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getSampleRate arginfo_class_OpusEncoder_getFinalRange

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_isPhaseInversionEnabled, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setPhaseInversion, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpusEncoder_getDtxState arginfo_class_OpusEncoder_isPhaseInversionEnabled

#define arginfo_class_OpusEncoder_getApplication arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getBitrate arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getComplexity arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getFrameDuration arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getChannelsForced arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getInbandFEC arginfo_class_OpusEncoder_isPhaseInversionEnabled

#define arginfo_class_OpusEncoder_getLookahead arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getLsbDepth arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getMaxBandwidth arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getPacketLossPercentage arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_isPredictionEnabled arginfo_class_OpusEncoder_isPhaseInversionEnabled

#define arginfo_class_OpusEncoder_getSignal arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getVbr arginfo_class_OpusEncoder_getFinalRange

#define arginfo_class_OpusEncoder_getVbrConstraint arginfo_class_OpusEncoder_getFinalRange

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setApplication, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, application, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setBandwidth, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, bandwidth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setBitrate, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, bitrate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setComplexity, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, complexity, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setDtxState, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, dtx, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setFrameDuration, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, frameDuration, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setChannelsForced, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, channels, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpusEncoder_setInbandFEC arginfo_class_OpusEncoder_setPhaseInversion

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setLsbDepth, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, lsb, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setMaxBandwidth, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, maxBandwidth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setPacketLossPercentage, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, packetLossPercentage, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpusEncoder_setPrediction arginfo_class_OpusEncoder_setPhaseInversion

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setSignal, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, signal, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpusEncoder_setVbrEnabled arginfo_class_OpusEncoder_setPhaseInversion

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_setVbrConstrained, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, constrained, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpusEncoder_encode, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, pcm, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, frameSize, IS_LONG, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(opus_version);
ZEND_METHOD(OpusEncoder, __construct);
ZEND_METHOD(OpusEncoder, __destruct);
ZEND_METHOD(OpusEncoder, reset);
ZEND_METHOD(OpusEncoder, getFinalRange);
ZEND_METHOD(OpusEncoder, getBandwidth);
ZEND_METHOD(OpusEncoder, getSampleRate);
ZEND_METHOD(OpusEncoder, isPhaseInversionEnabled);
ZEND_METHOD(OpusEncoder, setPhaseInversion);
ZEND_METHOD(OpusEncoder, getDtxState);
ZEND_METHOD(OpusEncoder, getApplication);
ZEND_METHOD(OpusEncoder, getBitrate);
ZEND_METHOD(OpusEncoder, getComplexity);
ZEND_METHOD(OpusEncoder, getFrameDuration);
ZEND_METHOD(OpusEncoder, getChannelsForced);
ZEND_METHOD(OpusEncoder, getInbandFEC);
ZEND_METHOD(OpusEncoder, getLookahead);
ZEND_METHOD(OpusEncoder, getLsbDepth);
ZEND_METHOD(OpusEncoder, getMaxBandwidth);
ZEND_METHOD(OpusEncoder, getPacketLossPercentage);
ZEND_METHOD(OpusEncoder, isPredictionEnabled);
ZEND_METHOD(OpusEncoder, getSignal);
ZEND_METHOD(OpusEncoder, getVbr);
ZEND_METHOD(OpusEncoder, getVbrConstraint);
ZEND_METHOD(OpusEncoder, setApplication);
ZEND_METHOD(OpusEncoder, setBandwidth);
ZEND_METHOD(OpusEncoder, setBitrate);
ZEND_METHOD(OpusEncoder, setComplexity);
ZEND_METHOD(OpusEncoder, setDtxState);
ZEND_METHOD(OpusEncoder, setFrameDuration);
ZEND_METHOD(OpusEncoder, setChannelsForced);
ZEND_METHOD(OpusEncoder, setInbandFEC);
ZEND_METHOD(OpusEncoder, setLsbDepth);
ZEND_METHOD(OpusEncoder, setMaxBandwidth);
ZEND_METHOD(OpusEncoder, setPacketLossPercentage);
ZEND_METHOD(OpusEncoder, setPrediction);
ZEND_METHOD(OpusEncoder, setSignal);
ZEND_METHOD(OpusEncoder, setVbrEnabled);
ZEND_METHOD(OpusEncoder, setVbrConstrained);
ZEND_METHOD(OpusEncoder, encode);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(opus_version, arginfo_opus_version)
	ZEND_FE_END
};


static const zend_function_entry class_OpusEncoder_methods[] = {
	ZEND_ME(OpusEncoder, __construct, arginfo_class_OpusEncoder___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, __destruct, arginfo_class_OpusEncoder___destruct, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, reset, arginfo_class_OpusEncoder_reset, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getFinalRange, arginfo_class_OpusEncoder_getFinalRange, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getBandwidth, arginfo_class_OpusEncoder_getBandwidth, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getSampleRate, arginfo_class_OpusEncoder_getSampleRate, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, isPhaseInversionEnabled, arginfo_class_OpusEncoder_isPhaseInversionEnabled, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setPhaseInversion, arginfo_class_OpusEncoder_setPhaseInversion, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getDtxState, arginfo_class_OpusEncoder_getDtxState, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getApplication, arginfo_class_OpusEncoder_getApplication, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getBitrate, arginfo_class_OpusEncoder_getBitrate, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getComplexity, arginfo_class_OpusEncoder_getComplexity, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getFrameDuration, arginfo_class_OpusEncoder_getFrameDuration, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getChannelsForced, arginfo_class_OpusEncoder_getChannelsForced, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getInbandFEC, arginfo_class_OpusEncoder_getInbandFEC, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getLookahead, arginfo_class_OpusEncoder_getLookahead, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getLsbDepth, arginfo_class_OpusEncoder_getLsbDepth, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getMaxBandwidth, arginfo_class_OpusEncoder_getMaxBandwidth, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getPacketLossPercentage, arginfo_class_OpusEncoder_getPacketLossPercentage, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, isPredictionEnabled, arginfo_class_OpusEncoder_isPredictionEnabled, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getSignal, arginfo_class_OpusEncoder_getSignal, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getVbr, arginfo_class_OpusEncoder_getVbr, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, getVbrConstraint, arginfo_class_OpusEncoder_getVbrConstraint, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setApplication, arginfo_class_OpusEncoder_setApplication, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setBandwidth, arginfo_class_OpusEncoder_setBandwidth, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setBitrate, arginfo_class_OpusEncoder_setBitrate, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setComplexity, arginfo_class_OpusEncoder_setComplexity, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setDtxState, arginfo_class_OpusEncoder_setDtxState, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setFrameDuration, arginfo_class_OpusEncoder_setFrameDuration, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setChannelsForced, arginfo_class_OpusEncoder_setChannelsForced, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setInbandFEC, arginfo_class_OpusEncoder_setInbandFEC, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setLsbDepth, arginfo_class_OpusEncoder_setLsbDepth, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setMaxBandwidth, arginfo_class_OpusEncoder_setMaxBandwidth, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setPacketLossPercentage, arginfo_class_OpusEncoder_setPacketLossPercentage, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setPrediction, arginfo_class_OpusEncoder_setPrediction, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setSignal, arginfo_class_OpusEncoder_setSignal, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setVbrEnabled, arginfo_class_OpusEncoder_setVbrEnabled, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, setVbrConstrained, arginfo_class_OpusEncoder_setVbrConstrained, ZEND_ACC_PUBLIC)
	ZEND_ME(OpusEncoder, encode, arginfo_class_OpusEncoder_encode, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
