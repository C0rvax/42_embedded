#include "spi.h"
#include "adc.h"
#include "prog.h" // Include the USART header

void	wheel(uint8_t pos)
{
	pos = 255 - pos;
	if (pos < 85)
		set_rgb(255 - pos * 3, 0, pos * 3);
	else if (pos < 170)
	{
		pos -= 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	}
	else
	{
		pos -= 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}

void	set_led(uint8_t rv1)
{
	switch (rv1 / 85)
	{
		case 3:
			APA102(2, 31, 255, 255, 255);
		case 2:
			APA102(1, 31, 255, 255, 255);
		case 1:
			APA102(0, 31, 255, 255, 255);
			break;
		case 0:
			APA102(4, 31, 255, 255, 255);
	}
}

// Process the command received via USART
void process_command(char *command)
{
	// Check if the command is "#FULLRAINBOW"
	if (strncmp(command, "#FULLRAINBOW", 12) == 0)
	{
		// Display a full rainbow effect
		for (uint8_t i = 0; i < 255; i++)
		{
			wheel(i);
			_delay_ms(10);
		}
	}
	// Check if the command is a color command
	else if (command[0] == '#' && strlen(command) == 10)
	{
		// Extract RGB values from the command
		uint8_t r = strtol(command + 1, NULL, 16);
		uint8_t g = strtol(command + 3, NULL, 16);
		uint8_t b = strtol(command + 5, NULL, 16);
		char led = command[7];
		// Set the color of the specified LED
		switch (led)
		{
			case 'D6':
				APA102(0, 31, r, g, b);
				break;
			case 'D7':
				APA102(1, 31, r, g, b);
				break;
			case 'D8':
				APA102(2, 31, r, g, b);
				break;
			default:
				usart_send_string("Error: Invalid LED\n");
				break;
		}
	}
	else
	{
		usart_send_string("Error: Invalid command\n");
	}
}

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();
	adc_init();
	usart_init(); // Initialize USART
	uint8_t rv1;
	char command[11];

    while (1)
    {
		rv1 = adc_read(0);
		set_led(rv1);
        // Read command from USART
		if (usart_read_command(command, 11))
		{
			process_command(command);
		}
    }
}
