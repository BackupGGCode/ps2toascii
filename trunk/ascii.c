/*
 * ascii.c
 *
 *  Created on: 2010-02-01
 *      Author: wooden
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "ascii.h"
#include "buffer.h"

struct ascii_decoder * ascii_create ()
{
	return ascii_create_size ( 1024 );
}

struct ascii_decoder * ascii_create_size (uint16_t size)
{
	struct ascii_decoder *ascii;

	ascii = (struct ascii_decoder * ) malloc (sizeof (struct ascii_decoder));
	ascii->keymap = PL_PROGRAMMER;
	ascii->data = buffer_create (size);
	buffer_clear (ascii->data);

	return ascii;
}

uint8_t ascii_decode (uint8_t key)
{
	return 0;
}
