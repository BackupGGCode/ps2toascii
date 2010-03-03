/*
 * ascii.c
 *
 *  Created on: 2010-02-01
 *      Author: wooden
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "decoder.h"
#include "buffer.h"

struct decoder * decoder_create ()
{
	return decoder_create_size ( 1024 );
}

struct decoder * decoder_create_size (uint16_t size)
{
	struct decoder_decoder *decoder;

	decoder = (struct decoder * ) malloc (sizeof (struct ascii_decoder));
	decoder->keymap = PL_PROGRAMMER;
	decoder->data = buffer_create (size);
	buffer_clear (decoder->data);

	return decoder;
}

uint8_t decode (uint8_t key)
{
	return 0;
}
