#include <avr/io.h>
#define UART_BAUDRATE 115200
#define F_CPU 16000000UL
#define MYUBRR ((unsigned char)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)) // Table 19-12 (p.165)

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // wait for empty buffer
	UDR0 = c; // send char
}

char	uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0))); // wait for char reception
	return UDR0; // return the value received
}

void	uart_init(unsigned char ubrr)
{	
	UBRR0L = (unsigned char)ubrr;
	UBRR0H = (unsigned char)(ubrr >> 8); // configure Baud rate
	
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // activate TX (transmission) and RX (reception)
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Mode 8N1 (8bits, no parity, 1 stop bit)
}

int	main(void)
{
	uart_init(MYUBRR);

	while (1)
	{
		char received = uart_rx(); // read a char
		uart_tx(received);
	}
	return 0;
}
