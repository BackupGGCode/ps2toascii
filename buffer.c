/*
 * buffer.c
 *
 *  Created on: 2010-01-31
 *      Author: wooden
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "buffer.h"
#include "ps2.h"

struct buffer * buffer_create(unsigned int size)
{
	struct buffer *buf;
	buf =  (struct buffer *) malloc (sizeof (struct buffer));

	if (buf != NULL)
	{
		buf->begin = (uint8_t *) malloc( sizeof (uint8_t) * (size));

		if (buf->begin != NULL)
				buf->size = size;
		else
			buf->size = 0;

		buf->end = &(buf->begin[buf->size - 1]);

	}
	return buf;
}

void buffer_dispose(struct buffer * buf)
{
	free (buf->begin);
	free (buf);
	buf = NULL;
}


void buffer_clear(struct buffer * buf)
{
	buf->counter = 0;
	buf->read = buf->begin;
	buf->write = buf->begin;
}


void buffer_read(struct buffer * buf, uint8_t *dest)
{
	GIMSK |= (0 << PS2_KBD_INT);
	if (buffer_is_empty(buf) == 0)
	{
		(*dest) = *(buf->read);
		if (buf->read != buf->end)
			buf->read++;
		else
			buf->read = buf->begin;
	}
	GIMSK |= (1 << PS2_KBD_INT);
}

void buffer_write(struct buffer * buf, uint8_t value)
{
	GIMSK |= (0 << PS2_KBD_INT);
	if (buffer_is_full (buf) == 0)
	{
		*(buf->write) = value;

		if (buf->write != buf->end)
			buf->write++;
		else
			buf->write = buf->begin;
	}
	GIMSK |= (01 << PS2_KBD_INT);
}

uint8_t buffer_is_empty (struct buffer * buf)
{
	if (buf->write == buf->read)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


uint8_t buffer_is_full (struct buffer * buf)
{
	if ( ((buf->write) +1) == buf->read)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
