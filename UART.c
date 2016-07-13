
#include <avr/io.h>
#include <avr/delay.h>

/** Example UART Code **/
// BAUDRATE : 9600
// STOP-BIT : 1
// DATA-BIT : 8
// Parity	: NONE

/** UBRR VALUES **/
// 2400bps	: 207
// 9600bps	: 51
// 14400bps	: 34
// 19200bps : 25

const int ubrr_value = 51;

void transmit(unsigned char data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}

unsigned char receive(void)
{
	while (!(UCSRA) & (1<<RXC));
	return UDR;
}

int main(void)
{
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
	UCSRB |= (1<<TXEN)|(1<<RXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	DDRB = 0x1;
	while(1)
	{
		// Transmit 'A' every 200ms
		transmit('A');
		_delay_ms(200);
	}
}
