#include "prog.h"

// Initialize the UART with the specified baud rate and frame format
void uart_init(void)
{
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8); // Configure the UBRR0H register (see section 20.11.1 of the doc)
    UBRR0L = (uint8_t)UBRR_VALUE; // Configure the UBRR0L register
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable reception and transmission (see section 20.11.2 of the doc)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure the frame format (8 bits) (see section 20.11.3 of the doc)
}

// Transmit a single character over UART
void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until the register is ready (see section 20.11.2 of the doc)
    UDR0 = c; // Send the character
}

// Transmit a null-terminated string over UART
void uart_tx_string(const char *str)
{
    while (*str)
        uart_tx(*str++); // Send each character of the string
}

// Receive a single character over UART
char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0))); // Wait for a character to be received (see section 20.11.3 of the doc)
    return UDR0; // Return the received character
}

// Print the status as a hexadecimal value over UART
void uart_print_status(uint8_t status)
{
    const char hex_digits[] = "0123456789ABCDEF";
//    uart_tx_string("0x");
    uart_tx(hex_digits[(status >> 4) & 0x0F]);
    uart_tx(hex_digits[status & 0x0F]);
    uart_tx(' ');
//    uart_tx_string("\r\n");
}

// Read a command from UART into the provided buffer with display and deletion support
uint8_t uart_read_command(char *command, uint8_t max_len)
{
    uint8_t i = 0;
    char c;
    uart_tx_string("> ");
    while (i < max_len - 1)
    {
        c = uart_rx();
        if (c == '\n' || c == '\r')
            break;
        if ((c == 127 || c == '\b') && i > 0)
        {
            uart_tx_string("\b \b");
            i--;
            continue;
        }
        if ((33 <= c && c <= 126) || c == 32) // Only process printable characters and spaces
        {
            uart_tx(c);
            command[i++] = c;
        }
    }
    command[i] = '\0';
    return i;
}
