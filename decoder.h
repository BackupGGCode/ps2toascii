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
#include "ps2.h"

enum DECODER_KEYMAP {PL_PROGRAMMER};
enum DECODER_ENCODING {ISO88952};
enum DECODER_STATE {LOL};

struct decoder
{
	enum DECODER_KEYMAP keymap;
	enum DECODER_ENCODING encoding;
	struct buffer *data;
	struct ps2_conn *conn;
	uint8_t counter;
};

struct decoder * decoder_create ();
struct decoder * decoder_create_size (uint16_t size);

uint8_t decoder_ps2_decode (struct ps_conn *conn);
uint8_t decoder_


#endif /* ASCII_H_ */
