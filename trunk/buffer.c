/*
 * buffer.c
 *
 *  Created on: 2010-01-31
 *      Author: wooden
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
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
	cli();
	if (buffer_is_empty(buf) == 0)
	{
		(*dest) = *(buf->read);
		if (buf->read != buf->end)
			buf->read++;
		else
			buf->read = buf->begin;

		buf->counter--;
	}
	sei();
}

void buffer_write(struct buffer * buf, uint8_t value)
{
	cli();
	if (buffer_is_full (buf) == 0)
	{
		*(buf->write) = value;

		if (buf->write != buf->end)
			buf->write++;
		else
			buf->write = buf->begin;

		buf->counter++;
	}
	sei();
}

uint8_t buffer_is_empty (struct buffer * buf)
{
	if (buf->counter == 0)
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
	if (buf->counter == buf->size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
