#include "prog.h"
#include "james.h"

void uart_init(void)
{
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8); // Configure the UBRR0H register (see section 20.11.1 of the doc)
    UBRR0L = (uint8_t)UBRR_VALUE; // Configure the UBRR0L register
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable reception and transmission (see section 20.11.2 of the doc)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure the frame format (8 bits) (see section 20.11.3 of the doc)
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until the register is ready (see section 20.11.2 of the doc)
    UDR0 = c; // Send the character
}

void uart_tx_string(const char *str)
{
    while (*str)
        uart_tx(*str++); // Send each character of the string
}

char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0))); // Wait for a character to be received (see section 20.11.3 of the doc)
    return UDR0; // Return the received character
}

void	uart_tx_hex16(uint16_t data)
{
	const char hex_digits[] = "0123456789abcdef";
    uart_tx(hex_digits[(data >> 12) & 0x0F]);
    uart_tx(hex_digits[(data >> 8) & 0x0F]);
	uart_tx(hex_digits[(data >> 4) & 0x0F]);
	uart_tx(hex_digits[data & 0x0F]);
}

void	uart_tx_hex8(uint8_t data)
{
	const char hex_digits[] = "0123456789abcdef";
	uart_tx(hex_digits[(data >> 4) & 0x0F]);
	uart_tx(hex_digits[data & 0x0F]);
}

uint8_t hex_char_to_uint8(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 20;
}

uint16_t uart_rx_hex(void)
{
    uint16_t value = 0;
    char c;
    while (1)
	{
        c = uart_rx();
        if (c == '\n' || c == '\r') break;
        if (c == 127 || c == '\b')
		{
			value = (value >> 4);
			uart_tx_string("\b \b");
		}
		if (hex_char_to_uint8(c) != 20)
		{
			value = (value << 4) | hex_char_to_uint8(c);
			uart_tx(c);
		}
    }
    return value;
}

void uart_rx_string(unsigned char *buffer, uint8_t max_length)
{
    uint8_t i = 0;
    uint8_t space = 0;
    char c;
    char quote = 0; // Variable to track if inside quotes
    uart_tx_string("> ");
    while (i < max_length - 1)
    {
        c = uart_rx();
        if (c == '\n' || c == '\r') break;
        if ((c == 127 || c == '\b') && i > 0)
        {
            uart_tx_string("\b \b");
            i--;
            continue;
        }
        if (c == '\'' || c == '"') // Toggle quote tracking
        {
            if (quote == c)
                quote = 0;
            else if (quote == 0)
                quote = c;
        }
        if (c == 32 && quote == 0) // Only process spaces if not inside quotes
        {
            if (!space)
                buffer[i++] = KEY;
            else if (space == 1)
                buffer[i++] = VALUE;
            else
                break;
            space++;
            uart_tx(c);
        }
        if ((33 <= c && c <= 126) || (c == 32 && quote)) // Only process printable characters and spaces inside quotes
        {
            uart_tx(c);
            buffer[i++] = c;
        }
    }
    buffer[i] = '\0';
}
