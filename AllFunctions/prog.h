#ifndef PROG_H
# define PROG_H

# include <avr/io.h>
# include <avr/interrupt.h>

# define F_CPU 16000000UL
# define UART_BAUDRATE 115200
# define UBRR_VALUE (uint16_t)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)
# define MAX_LEN 16

/**
 * @brief Initialize the UART.
 */
void uart_init(void);

/**
 * @brief Transmit a character via UART.
 * 
 * @param c The character to transmit.
 */
void uart_tx(char c);

/**
 * @brief Transmit a string via UART.
 * 
 * @param str The string to transmit.
 */
void uart_tx_string(const char *str);

/**
 * @brief Receive a character via UART.
 * 
 * @return The received character.
 */
char uart_rx(void);

/**
 * @brief Transmit an 8-bit hexadecimal value via UART.
 * 
 * @param data The 8-bit data to transmit.
 */
void uart_tx_hex8(uint8_t data);

/**
 * @brief Transmit a 16-bit hexadecimal value via UART.
 * 
 * @param data The 16-bit data to transmit.
 */
void uart_tx_hex16(uint16_t data);

/**
 * @brief Convert a hexadecimal character to an 8-bit unsigned integer.
 * 
 * @param c The hexadecimal character.
 * @return The corresponding 8-bit unsigned integer.
 */
uint8_t hex_char_to_uint8(char c);

/**
 * @brief Receive a 16-bit hexadecimal value via UART.
 * 
 * @return The received 16-bit hexadecimal value.
 */
uint16_t uart_rx_hex(void);

/**
 * @brief Receive a string via UART.
 * 
 * @param buffer The buffer to store the received string.
 * @param max_length The maximum length of the string.
 */
void uart_rx_string(unsigned char *buffer, uint8_t max_length);

#endif /* __PROG_H__ */
