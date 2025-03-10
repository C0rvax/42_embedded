#include "prog.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    adc_init(); // Init ADC
	uart_init(); // Init UART
	char	value[3];
    while (1)
	{
		uint8_to_hex(adc_read(0), value);
		uart_tx_string(value);
		uart_tx_string("\r\n");
        _delay_ms(20); // Wait 20ms
    }

    return 0;
}

