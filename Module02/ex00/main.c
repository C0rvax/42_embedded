#include <avr/io.h>
#include <util/delay.h>

// UBRRn USART Baud Rate Register
// UCSR USART Control and Status Register
// UCSZ USART Character SiZe
// UPM UART Parity Mode
// USBS UART Stop Bit Setting

#define UART_BAUDRATE 115200
#define F_CPU 16000000UL
#define MYUBRR ((unsigned char)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)) // Table 19-12 (p.165)

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // wait for empty buffer (p.159)
	UDR0 = c; // send char
}

void	uart_init(unsigned char ubrr)
{	
	UBRR0L = (unsigned char)ubrr; // (p.162)
	UBRR0H = (unsigned char)(ubrr >> 8); // configure Baud rate (p.162)
	
	UCSR0B = (1 << TXEN0); // TX ENable (transmission) (p.160)
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Mode 8N1 (8bits, no parity, 1 stop bit) (p.162) : 8 bits of data
	UCSR0C &= ~(1 << UPM01) & ~(1 << UPM00); // Mode 8N1 : no parity (p.161)
	UCSR0C &= ~(1 << USBS0); // Mode 8N1 : 1 stop bit (p.161)
}

int	main(void)
{
	uart_init(MYUBRR);
	_delay_ms(100);
	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
	return 0;
}
