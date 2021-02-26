#ifndef _ENCODER_H
#define _ENCODER_H

#include "opus.h"
#include "php.h"

#define OPUS_ENCODER_GET(methodName, resultType, op, returnMacro) \
	PHP_METHOD(OpusEncoder, methodName) \
	{ \
		opus_encoder_t *self = Z_OPUS_ENCODER_P(ZEND_THIS); \
		resultType result; \
		int err = opus_encoder_ctl(self->encoder, op(&result)); \
		HANDLE_OPUS_ERR(err, "could not methodName"); \
		returnMacro; \
	}

typedef struct opus_encoder_t {
    OpusEncoder *encoder;
    zend_object std;
} opus_encoder_t;

extern zend_object_handlers opus_encoder_object_handlers;
extern zend_class_entry *opus_encoder_ce;

zend_object *opus_encoder_new(zend_class_entry *ce);

#endif