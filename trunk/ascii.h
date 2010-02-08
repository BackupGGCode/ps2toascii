/*
 * ascii.h
 *
 *  Created on: 2010-02-01
 *      Author: wooden
 */

#ifndef ASCII_H_
#define ASCII_H_


#include <stdint.h>
#include "buffer.h"

enum ASCII_KEYMAP {PL_PROGRAMMER};
enum ASCII_STATE {LOL};

struct ascii_decoder
{
	enum ASCII_KEYMAP keymap;
	struct buffer *data;
	struct buffer *temp;
	uint8_t counter;
};

struct ascii_decoder * ascii_create ();
struct ascii_decoder * ascii_create_size (uint16_t size);

uint8_t ascii_decode (uint8_t key);


#endif /* ASCII_H_ */
