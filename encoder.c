#include "encoder.h"
#include "helpers.h"

zend_object *opus_encoder_new(zend_class_entry *ce)
{
	opus_encoder_t *encoder = zend_object_alloc(sizeof(opus_encoder_t), ce);

	zend_object_std_init(&encoder->std, ce);
	encoder->std.handlers = &opus_encoder_object_handlers;
	return &encoder->std;
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

	if (! validate_application(application)) {
		THROW(-1, invalid_application_error, application);
	}

	encoder = opus_encoder_create((opus_int32)sample_rate, channels, application, &err);
	HANDLE_OPUS_ERR(err, "could not create new opus encoder");

	self->encoder = encoder;
	self->channels = channels;
}

PHP_METHOD(OpusEncoder, __destruct)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	opus_encoder_destroy(self->encoder);
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

	if (! validate_bandwidth(bandwidth, true)) {
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

PHP_METHOD(OpusEncoder, setInbandFEC)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_bool fec;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(fec)
	ZEND_PARSE_PARAMETERS_END();
	
	int err = opus_encoder_ctl(self->encoder, OPUS_SET_INBAND_FEC(fec));
	HANDLE_OPUS_ERR(err, "could not set forced channels");
}

PHP_METHOD(OpusEncoder, setLsbDepth)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long lsb_depth;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(lsb_depth)
	ZEND_PARSE_PARAMETERS_END();
	
	if (lsb_depth < 8 || lsb_depth > 24) {
		THROW(0, "LSB depth must be between 8 and 24 inclusive, got %ld", lsb_depth);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_LSB_DEPTH(lsb_depth));
	HANDLE_OPUS_ERR(err, "could not set lsb depth");
}

PHP_METHOD(OpusEncoder, setMaxBandwidth)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long max_bandwidth;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(max_bandwidth)
	ZEND_PARSE_PARAMETERS_END();
	
	if (! validate_bandwidth(max_bandwidth, false)) {
		THROW(0, invalid_bandwidth_error, max_bandwidth);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_MAX_BANDWIDTH(max_bandwidth));
	HANDLE_OPUS_ERR(err, "could not set max bandwidth");
}

PHP_METHOD(OpusEncoder, setPacketLossPercentage)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long packet_loss_percentage;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(packet_loss_percentage)
	ZEND_PARSE_PARAMETERS_END();
	
	if (packet_loss_percentage < 0 || packet_loss_percentage > 100) {
		THROW(0, "packet loss percentage must be between 0 and 100 inclusive, got %ld", packet_loss_percentage);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_PACKET_LOSS_PERC(packet_loss_percentage));
	HANDLE_OPUS_ERR(err, "could not set packet loss percentage");
}

PHP_METHOD(OpusEncoder, setPrediction)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_bool prediction;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(prediction)
	ZEND_PARSE_PARAMETERS_END();
	
	int err = opus_encoder_ctl(self->encoder, OPUS_SET_PREDICTION_DISABLED(!prediction));
	HANDLE_OPUS_ERR(err, "could not set prediction");
}

PHP_METHOD(OpusEncoder, setSignal)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_long signal;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(signal)
	ZEND_PARSE_PARAMETERS_END();

	if (! validate_signal(signal)) {
		THROW(0, invalid_signal_error, signal);
	}

	int err = opus_encoder_ctl(self->encoder, OPUS_SET_SIGNAL(signal));
	HANDLE_OPUS_ERR(err, "could not set signal");
}

PHP_METHOD(OpusEncoder, setVbrEnabled)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_bool enabled;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	
	int err = opus_encoder_ctl(self->encoder, OPUS_SET_VBR(enabled));
	HANDLE_OPUS_ERR(err, "could not set vbr state");
}

PHP_METHOD(OpusEncoder, setVbrConstrained)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zend_bool constrained;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(constrained)
	ZEND_PARSE_PARAMETERS_END();
	
	int err = opus_encoder_ctl(self->encoder, OPUS_SET_VBR_CONSTRAINT(constrained));
	HANDLE_OPUS_ERR(err, "could not set vbr constraint state");
}

PHP_METHOD(OpusEncoder, encode)
{
	opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS);
	zval *val, *zend_pcm;
	zend_array *retval;
	uint32_t i = 0;
	int32_t count;
	opus_int16 *pcm;
	unsigned char *output;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY(zend_pcm)
	ZEND_PARSE_PARAMETERS_END();

 	pcm = (opus_int16*) malloc(sizeof(*pcm)*zend_pcm->value.arr->nNumOfElements);

	// convert zend array to opus array
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zend_pcm), val)
	{
		pcm[i++] = (opus_int16)val->value.lval;
	}
	ZEND_HASH_FOREACH_END();

	// calculate frame size and output max size
	// this is wrong - needs to be changed, but it does output the correct
	// opus, just uses too much memory to do so
	int frame_size = zend_pcm->value.arr->nNumOfElements/self->channels;
	int output_size = frame_size*self->channels*2;
	output = (unsigned char*) malloc(sizeof(*output)*output_size);

	// encode the PCM into opus
	count = opus_encode(self->encoder, (const opus_int16*) pcm, frame_size, output, output_size);

	// if `opus_encode` returns less than 0 it indicates an error
	if (count < 0) {
		THROW(count, opus_strerror(count), NULL);
	}

	// convert the C array back into a PHP zend array
	retval = zend_new_array(count);

	for (i = 0; i < count; i++) {
		ZVAL_LONG(val, output[i]);
		zend_hash_index_add(retval, i, val);
	}
	
	// return and clean up
	RETVAL_ARR(retval);

	free(output);
	free(pcm);
}