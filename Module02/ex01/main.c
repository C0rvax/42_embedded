#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// UBRRn USART Baud Rate Register
// UCSR USART Control and Status Register
// UCSZ USART Character SiZe

#define UART_BAUDRATE 115200
#define F_CPU 16000000UL
#define MYUBRR ((unsigned char)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)) // Table 19-12 (p.165)

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // wait for empty buffer (p.159)
	UDR0 = c; // send char
}

void	uart_tx_string(const char *str)
{
	while (*str)
		uart_tx(*str++);
}

void	uart_init(unsigned char ubrr)
{	
	UBRR0L = (unsigned char)ubrr; // (p.162)
	UBRR0H = (unsigned char)(ubrr >> 8); // configure Baud rate (p.162)
	
	UCSR0B = (1 << TXEN0); // TX ENable (transmission) (p.160)
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Mode 8N1 (8bits, no parity, 1 stop bit) (p.162)
}

void	timer1_init(void)
{
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // mode 4 (CTC) with 1024 prescaler
	OCR1A = ((F_CPU / 1024) * 2) - 1; // TOP = freq / prescaler * 2seconds - 1 (start at 0)
	TCNT1 = 0;
	TIMSK1 |= (1 << OCIE1A); // activate interrupt (TIMer MaSk) (p.112)
	sei(); // enable global interrupts
}

ISR(TIMER1_COMPA_vect)
{
	uart_tx_string("Hello World!\r\n");
}

int	main(void)
{
	uart_init(MYUBRR);
	timer1_init();

	while (1);
	return 0;
}
