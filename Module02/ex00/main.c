#include <avr/io.h>
#include <util/delay.h>
#define UART_BAUDRATE 115200
#define F_CPU 16000000UL
#define MYUBBR (F_CPU / (16 * UART_BAUDRATE))-1

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // wait for empty buffer
	UDR0 = c; // send char
}

void	uart_init(unsigned int ubbr)
{	
	UBRR0L = (unsigned char)ubbr;
	UBRR0H = (unsigned char)(ubbr >> 8); // configure Baud rate
	
	UCSR0B = (1 << TXEN0); // activate TX (transmission)
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Mode 8N1 (8bits, no parity, 1 stop bit)
}

int	main()
{
	uart_init(MYUBBR);
	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
	return 0;
}
