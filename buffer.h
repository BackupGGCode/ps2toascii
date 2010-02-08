/*
 * buffer.h
 *
 *  Created on: 2010-01-31
 *      Author: wooden
 */

#ifndef BUFFER_H_
#define BUFFER_H_

struct buffer
{
	unsigned int size;
	unsigned int counter;
	uint8_t *end;
	uint8_t *begin;
	volatile uint8_t *read;
	volatile uint8_t *write;

};

struct buffer * buffer_create(unsigned int size);
void buffer_dispose(struct buffer * buf);
void buffer_clear(struct buffer * buf);

void buffer_read (struct buffer * buf, uint8_t *dest);
void buffer_write (struct buffer * buf, uint8_t value);
void buffer_get (struct buffer * buf, uint8_t *dest);

uint8_t buffer_is_empty (struct buffer * buf);
uint8_t buffer_is_full (struct buffer * buf);


#endif /* BUFFER_H_ */
