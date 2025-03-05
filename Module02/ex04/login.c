#include "login.h"

void	acceptUser(void)
{
	uart_tx_string(WELCOME);
	for (unsigned char i = 0; i < 25; i++) // 25 is 5 cycles
	{
		if (i % 5 != 3)
		{
			PORTB ^= (1 << i % 5);
			_delay_ms(200);
			PORTB ^= (1 << i % 5);
		}
	}
}

void	drama(void)
{
	uart_tx_string("Verifying ");
	unsigned char i = 0;
	while (++i < 4)
	{
		_delay_ms(1000);
		uart_tx('.');
	}
	_delay_ms(1000);
	uart_tx_string("\r\n");
}

void	login(void)
{
	char username[MAX_LEN], password[MAX_LEN];

	while (1)
	{
		uart_tx_string("\r\nEnter your login:\r\n\tusername: ");
		get_input(username, 0);
		uart_tx_string("\tpassword: ");
		get_input(password, 1);
		drama();

		if (!strcmp(username, USER) && !strcmp(password, PASS))
		{
			acceptUser();
			return;
		}
		else
			uart_tx_string("\r\nBad combination username/password\r\n");
	}
}
