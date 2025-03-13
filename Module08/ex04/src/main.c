#include "spi.h"
#include "adc.h"
#include "prog.h" // Include the USART header
#include <string.h> // Include string.h for strncmp, strlen, and strtol
#include <stdlib.h> // Include stdlib.h for strtol

void	set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	// Implement the function to set RGB values
	// This is a placeholder implementation
	APA102(0, 31, red, green, blue);
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
	{
        if (*str1 != *str2)
            return (unsigned char)*str1 - (unsigned char)*str2;
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

void putnbr2(uint8_t n)
{
    if (n >= 10)
        putnbr2(n / 10);
    uart_tx((n % 10) + '0');
}

uint8_t ft_strlen(const char* str)
{
	uint8_t len = 0;
	while (str[len])
		len++;
	return len;
}

uint8_t my_strtol16(const char* str)
{
    uint8_t result = 0;

    while (*str)
	{
        uint8_t digit;

        if (*str >= '0' && *str <= '9')
            digit = *str - '0';
        else if (*str >= 'a' && *str <= 'f')
            digit = *str - 'a' + 10;
        else if (*str >= 'A' && *str <= 'F')
            digit = *str - 'A' + 10;
        else
            break;

        if (result > (255 - digit) / 16)
            return 255;

        result = result * 16 + digit;
        str++;
    }
    return result;
}

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
	if (strcmp(command, "#FULLRAINBOW") == 0)
	{
		// Display a full rainbow effect
		for (uint8_t i = 0; i < 255; i++)
		{
			wheel(i);
			_delay_ms(10);
		}
	}
	// Check if the command is a color command
	else if (command[0] == '#' && ft_strlen(command) == 9)
	{
		// Extract RGB values from the command
		uint8_t r = my_strtol16(command + 1);
		uint8_t g = my_strtol16(command + 3);
		uint8_t b = my_strtol16(command + 5);
		char led = command[7];
		// Set the color of the specified LED
		switch (led)
		{
			case '6':
				APA102(0, 31, r, g, b);
				break;
			case '7':
				APA102(1, 31, r, g, b);
				break;
			case '8':
				APA102(2, 31, r, g, b);
				break;
			default:
				uart_tx_string("Error: Invalid LED\n");
				break;
		}
	}
	else
	{
		uart_tx_string("Error: Invalid command\n");
	}
}

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();
	adc_init();
	uart_init(); // Initialize USART
	uint8_t rv1;
	char command[13]; // Increase size to 13 to accommodate "#FULLRAINBOW" and null terminator

    while (1)
    {
		rv1 = adc_read(0);
		set_led(rv1);
        // Read command from USART
		if (uart_read_command(command, 13))
		{
			process_command(command);
		}
    }
}
