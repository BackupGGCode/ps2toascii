/*
 * ps2.c
 *
 *  Created on: 2010-01-31
 *      Author: wooden
 */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/parity.h>
#include "ps2.h"



uint8_t ps2_check_parity_odd(struct  ps2_conn *conn)
{
	if (parity_even_bit(conn->data) == 0)
		return 1;
	else
		return 0;

}

void ps2_conn_clear (struct ps2_conn *conn)
{
	conn->state = IDLE;
	conn->counter = START;
	conn->data = 0;
}

struct ps2_conn * ps2_conn_create (void)
{
	return ps2_conn_create_size (10);
}

struct ps2_conn * ps2_conn_create_size (unsigned int buf_size)
{
	struct ps2_conn *conn;
	conn = (struct ps2_conn *) malloc (sizeof (struct ps2_conn) );

	conn->rx_buf = buffer_create (buf_size);
	conn->tx_buf = buffer_create (buf_size);

	buffer_clear (conn->tx_buf);
	buffer_clear (conn->rx_buf);

	ps2_conn_clear (conn);
	return conn;

}


void ps2_handle (struct ps2_conn *conn)
{


	switch (conn->state)
	{
		case IDLE:
			if (ps2_tx_is_not_empty(conn) == 1)
				ps2_prepare_recive (conn);
			else
				ps2_prepare_recive (conn);


			//break;

		case RECIVING:

			if (conn->counter == START)
			{
				if ( PS2_DATA_IN  & (1 << PS2_DATA_PIN) )
				{
					ps2_error (conn);
				}
				conn->counter++;
			}

			else if ((conn->counter >= D0) && (conn->counter <= D7))
			{
				conn ->data |= ((( PS2_DATA_IN & ( 1 << PS2_DATA_PIN ) ) >> PS2_DATA_PIN)  << (int8_t) conn->counter );
				conn->counter++;
			}

			else if (conn->counter == PARITY)
			{
				if (ps2_check_parity_odd (conn) != ( ( PS2_DATA_IN & ( 1 << PS2_DATA_PIN ) ) >>  PS2_DATA_PIN ))
				{
					ps2_error (conn);
				}
				conn->counter++;
			}

			else if (conn->counter == STOP)
			{
				if ( PS2_DATA_IN & (0 << PS2_DATA_PIN ))
				{
					ps2_error (conn);
				}
				else
				{
					buffer_write (conn->rx_buf, conn->data);
					ps2_conn_clear (conn);
				}
			}

			break;

		case TRANSMITING: ;
			break;

		case ERROR:
			ps2_transmit (conn, RESEND);
			ps2_prepare_transmit (conn);
			break;
	}

}

void ps2_analyze_rx (struct ps2_conn *conn)
{
	volatile uint8_t temp;

	buffer_read (ps2->rx_buf, &temp);

	switch (temp)
	{
		case 0xF0:
		buffer_read (ps2->rx_buf, &temp);
		
		case 0x

		break;
	}
}

void ps2_recive (struct ps2_conn *conn)
{

}

void ps2_transmit (struct ps2_conn *conn, enum TR_MSG msg)
{
	buffer_write (conn->tx_buf,  (uint8_t) msg);
}

void ps2_prepare_recive(struct ps2_conn *conn)
{
	//conn->state = RECIVING;
	conn->state = RECIVING;
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);					// set low edge interrupt
}

void ps2_prepare_transmit(struct ps2_conn *conn)
{
	conn->state = TRANSMITING;
	MCUCR |= (1 << ISC01) | (1 << ISC00);					// set high edge interrupt
}

void ps2_error (struct ps2_conn *conn)
{
	conn->state = ERROR;
}

uint8_t ps2_tx_is_not_empty(struct ps2_conn *conn)
{
	if (buffer_is_empty (conn->tx_buf) == 1)
		return 0;
	else
		return 1;
}

