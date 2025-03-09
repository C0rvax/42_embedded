#include "prog.h"

void uart_init(void)
{
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_tx_string(const char *str)
{
    while (*str)
        uart_tx(*str++);
}

char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void get_input(char* buffer, uint8_t hide)
{
    uint8_t i = 0;
    while (1) 
	{
		char c = uart_rx(); // read received char
		if (c == '\n' || c == '\r') // on rx send a \r\n when press enter
		{
			buffer[i] = '\0';
			uart_tx_string("\r\n");
			return;
		}
		else if ((c == '\b' || c == 127) && i > 0)  // Backspace and not empty
		{
			uart_tx_string("\b \b"); // back/space/back to replace the char
			i--;
		}
		else if (i < MAX_LEN - 1)
		{
			buffer[i++] = c;
			uart_tx(hide ? '*' : c);
		}
	}
}
