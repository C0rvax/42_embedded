#ifndef PROG_H
# define PROG_H

# include <avr/io.h>

# define F_CPU 16000000UL
# define UART_BAUDRATE 115200
# define UBRR_VALUE (uint16_t)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)
# define MAX_LEN 16

void uart_init(void);
void uart_tx(char c);
void uart_tx_string(const char *str);
char uart_rx(void);
void	uart_print_status(uint8_t status);

#endif /* PROG_H */
