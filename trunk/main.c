/*
 * main.c
 *
 *  Created on: 2009-12-12
 *      Author: wooden
 */

#include <avr/interrupt.h>
#include "ps2.h"

struct ps2_conn *ps2;

ISR(INT0_vect )
{
	extern struct ps2_conn *ps2;
    ps2_handle(ps2);
	//buffer_read(ps2->rx_buf, (uint8_t *) & PORTC);
/*
    if (PORTC == 0xff)
    	PORTC = 0x00;
    else
    	PORTC = 0xff;
*/
}

int main ( void )
{

	extern struct ps2_conn *ps2;
	ps2 = ps2_conn_create();

	DDRC=0xff;

	DDRA = 0xfc;

	//PORTA =0xFF;
	GICR |= (1 << PS2_KBD_INT);
	GIMSK |= (1 << PS2_KBD_INT);
	  // TCCR0 |= (1<<CS00);
	   // TIMSK |= (1<<TOIE0);

	ps2_prepare_recive (ps2);

    sei();

	for (;;)
	{
		DDRC=0xff;
		PORTC += 1;
	}

	return 0;
}
