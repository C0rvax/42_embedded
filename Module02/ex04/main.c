#include "login.h"

int main(void)
{
	uart_init();
	login();
	while (1);
	return 0;
}
