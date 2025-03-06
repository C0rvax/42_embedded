#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#define RED PD5
#define GREEN PD6
#define BLUE PD3
#define OCRED OCR0B
#define OCGREEN OCR0A
#define OCBLUE OCR2B

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200
#define MYUBRR F_CPU/16.0/UART_BAUDRATE-0.5

void	init_uart(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Enable reception and transmission
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits of data, 1 stop bit
}

char	uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0))); // wait for reception
    return UDR0;
}

void	uart_tx(char data)
{
    while (!(UCSR0A & (1 << UDRE0))); // wait for an empty buffer
    UDR0 = data;
}

void	uart_send_string(char *str)
{
    while (*str)
        uart_tx(*str++);
}

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCRED = r; // Sortie rouge
    OCGREEN = g; // Sortie verte
    OCBLUE = b; // Sortie bleue
}

void	init_rgb(void)
{
	DDRD |= (1 << RED) | (1 << GREEN) | (1 << BLUE);  // PD3 (OC2B - blue), PD5 (OC0B - red), PD6 (OC0A - green)

    // Config timers in mode Fast PWM
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
    TCCR0B = (1 << CS01);  // Prescaler 8

    TCCR2A = (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
    TCCR2B = (1 << CS21);  // Prescaler 8
}

void	parse_rgb(char* str)
{
    if (str[0] == '#' && strlen(str) == 7) // Check format #RRGGBB
	{
        char rs[3] = {str[1], str[2], '\0'};
        char gs[3] = {str[3], str[4], '\0'};
        char bs[3] = {str[5], str[6], '\0'};

        uint8_t r = strtol(rs, NULL, 16);
        uint8_t g = strtol(gs, NULL, 16);
        uint8_t b = strtol(bs, NULL, 16);

        set_rgb(r, g, b);
    }
}

int	main(void)
{
    init_uart(MYUBRR);
    init_rgb();

    char buffer[8] = {0};
    uint8_t index = 0;

    uart_send_string("UART Ready\r\n");
    uart_send_string("\tUsage #RRGGBB\r\n\t");

    while (1)
	{
        char c = uart_rx();

		uart_tx(c);
        if (c == '\b' || c == 127)
			uart_send_string("\b \b");
        if (c == '\n' || c == '\r') // EOF
		{
			uart_send_string("\r\n\t");
            buffer[index] = '\0';
            parse_rgb(buffer);
            index = 0;
        }
		else if (index < 7)
            buffer[index++] = c;
    }
}

