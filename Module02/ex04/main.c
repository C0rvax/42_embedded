#include "login.h"

int main(void)
{
	uart_init();
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
	login();
	while (1);
	return 0;
}
