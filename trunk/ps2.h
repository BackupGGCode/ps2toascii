/*
 * ps2.h
 *
 *  Created on: 2010-01-31
 *      Author: wooden
 */

/*struct ps2_frame
{
	unsigned int stop   : 1;
	unsigned int parity : 1;
	unsigned int data	: 8;
	unsigned int start	: 1;
};*/

#ifndef PS2_H_
#define PS2_H_

#define PS2_DATA_PIN 0
#define PS2_DATA_IN PINA
#define PS2_KBD_INT INT0

#include <stdint.h>
#include "buffer.h"

enum STATE {TRANSMITING, RECIVING, IDLE, ERROR};
enum COUNTER {START = -1, D0 = 0, D1 = 1, D2 = 2, D3 = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7, PARITY = 8 , STOP = 9};
enum TR_MSG {RESEND = 0xFE};

struct ps2_conn
{
	volatile enum STATE state;
	struct buffer *tx_buf;
	struct buffer *rx_buf;
	enum COUNTER counter;
	uint8_t data;
};


uint8_t ps2_check_parity_odd(struct ps2_conn *conn);

void ps2_handle (struct ps2_conn *conn);
void ps2_conn_clear (struct ps2_conn *conn);

struct ps2_conn * ps2_conn_create_size (unsigned int buf_size);
struct ps2_conn * ps2_conn_create (void);

void ps2_send (struct ps2_conn *conn, enum TR_MSG msg);

void ps2_prepare_transmit (struct ps2_conn *conn);
void ps2_prepare_recive (struct ps2_conn *conn);

void ps2_transmit (struct ps2_conn *conn, enum TR_MSG);
void ps2_recive (struct ps2_conn *conn);

void ps2_error (struct ps2_conn *conn);

uint8_t ps2_tx_is_not_empty(struct ps2_conn *conn);

#endif /* PS2_H_ */
