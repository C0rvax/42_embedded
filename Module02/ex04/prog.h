#ifndef PROG_H
# define PROG_H

# include <avr/io.h>

# define F_CPU 16000000UL
# define UART_BAUDRATE 115200
# define UBRR_VALUE (unsigned char)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)
# define MAX_LEN 16

void uart_init(void);
void uart_tx(char c);
void uart_tx_string(const char *str);
char uart_rx(void);
void get_input(char* buffer, uint8_t hide);

#endif /* __PROG_H__ */
