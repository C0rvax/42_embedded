#ifndef PROG_H
# define PROG_H

# include <avr/io.h>
# include <avr/interrupt.h>

# define F_CPU 16000000UL
# define UART_BAUDRATE 115200
# define UBRR_VALUE (uint16_t)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)
# define MAX_LEN 16

void	uart_init(void);
void	uart_tx(char c);
void	uart_tx_string(const char *str);
char	uart_rx(void);
void	uart_tx_hex8(uint8_t data);
void	uart_tx_hex16(uint16_t data);
uint8_t hex_char_to_uint8(char c);
uint16_t uart_rx_hex(void);
void	uart_rx_string(unsigned char *buffer, uint8_t max_length);

#endif /* __PROG_H__ */
