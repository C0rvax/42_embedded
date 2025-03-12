#include "prog.h"
#include "i2c.h"
#include <util/twi.h>

int main(void)
{
	uart_init(); // Init UART
	i2c_init();

	while (1)
	{
		i2c_start();
		i2c_write_status("i2c Start status : ");
		i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
		i2c_write_status("i2c Write addr status : ");
		i2c_stop();
	}
}

