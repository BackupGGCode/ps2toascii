/*
 * main.c
 *
 *  Created on: 2009-12-12
 *      Author: wooden
 */

#include <avr/interrupt.h>
#include <util/parity.h>
#include "ps2.h"
#include "buffer.h"

struct ps2_conn *ps2;

ISR(INT0_vect )
{
	extern struct ps2_conn *ps2;
    ps2_handle(ps2);
    buffer_read (ps2->rx_buf, (uint8_t *) &PORTC);
}

int main ( void )
{

	struct buffer *buf;
	buf = buffer_create (2);
	
	extern struct ps2_conn *ps2;
	ps2 = ps2_conn_create();

	DDRC=0xff;

	DDRA = 0xfc;

	GICR |= (1 << PS2_KBD_INT);
	GIMSK |= (1 << PS2_KBD_INT);

	ps2_prepare_recive (ps2);

    sei();
/*
	buffer_clear(buf);
	
	buffer_write (buf, 8);
	buffer_write (buf, 16);
	buffer_write (buf, 32);

	buffer_read (buf, (uint8_t *) &DDRC);
	buffer_read (buf, (uint8_t *) &DDRC);
	buffer_read (buf, (uint8_t *) &DDRC);
*/	

	while (1)
	{
		DDRB ++;
	}

	return 0;
}
