#include "prog.h"

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
