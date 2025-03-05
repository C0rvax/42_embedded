#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200
#define UBRR_VALUE (unsigned char)((F_CPU / (16.0 * UART_BAUDRATE)) - 0.5)

#define MAX_LEN 16

const char* correct_username = "c0rvax";
const char* correct_password = "nope";

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

void get_input(char *buffer, uint8_t max_len, uint8_t hide)
{
    uint8_t i = 0;
    char c;
    while (1) 
	{
		c = uart_rx();
		if (c == '\r' || c == '\n')  // Enter
		{
			buffer[i] = '\0';
			uart_tx_string("\r\n");
			return;
		}
		else if (c == '\b')  // Backspace
		{
			if (i > 0)
			{
				i--;
				uart_tx_string("\b \b"); // back space back to replace the char
			}
		}
		else if (i < max_len - 1)
		{
			buffer[i++] = c;
			uart_tx(hide ? '*' : c);
		}
	}
}

void login(void)
{
	char username[MAX_LEN], password[MAX_LEN];

	while (1)
	{
		uart_tx_string("\r\nEnter your login:\r\n");
		uart_tx_string("\tusername: ");
		get_input(username, MAX_LEN, 0);
		uart_tx_string("\tpassword: ");
		get_input(password, MAX_LEN, 1);

		uart_tx_string("\r\nVerifying ");
		_delay_ms(1000);
		uart_tx('.');
		_delay_ms(1000);
		uart_tx('.');
		_delay_ms(1000);
		uart_tx('.');
		_delay_ms(1000);
		uart_tx_string("\r\n"); // Dramatic effect

		if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0)
		{
			uart_tx_string("\r\nHello c0rvax!\r\nShall we play a game? tintintin!!!\r\n");
			for (int i = 0; i < 5; i++)
			{
				PORTB ^= (1 << PORTB5);  // Clignotement LED
				_delay_ms(500);
			}
			return;
		}
		else
			uart_tx_string("\r\nBad combination username/password\r\n");
	}
}

int main(void) {
	uart_init();
	DDRB |= (1 << DDB5);  // Configurer la LED intégrée
	login();
	while (1);
	return 0;
}

