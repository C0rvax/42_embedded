#include "spi.h"
#include "prog.h" // Include the USART header

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

void	set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint8_t i = 0; i < 4; i++)
		SPI_MasterTransmit(0x00); // Initialize sequence (4o to 0)
	for (uint8_t i = 0; i < 5; ++i)
		APA102_send(BRIGHTNESS, red, green, blue);
	for (uint8_t i = 0; i < 4; i++)
		SPI_MasterTransmit(0xFF);
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

void process_command(char *command)
{
	if (strcmp(command, "#FULLRAINBOW") == 0)
	{
		for (uint16_t i = 0; i < 767; i++) // 3 * 256 -1
		{
			wheel(i % 255);
			_delay_ms(10);
		}
		APA102(4, 0, 0, 0, 0); // Turn off led
		uart_tx_string("\r\n");
	}
	else if (command[0] == '#' && ft_strlen(command) == 9)
	{
		char rs[3] = {command[1], command[2], '\0'};
		char gs[3] = {command[3], command[4], '\0'};
		char bs[3] = {command[5], command[6], '\0'};
		// Extract RGB values from the command
		uint8_t r = my_strtol16(rs);
		uint8_t g = my_strtol16(gs);
		uint8_t b = my_strtol16(bs);
		char led;
		if (command[7] != 'D')
			led = 0;
		else
			led = command[8];
		switch (led) // Set the color of the specified LED
		{
			case '6':
				APA102(0, BRIGHTNESS, r, g, b);
				break;
			case '7':
				APA102(1, BRIGHTNESS, r, g, b);
				break;
			case '8':
				APA102(2, BRIGHTNESS, r, g, b);
				break;
			default:
				uart_tx_string("\nError: Invalid LED\r\nUsage: #RRGGBBDX (DX: D6, D7, D8)");
				break;
		}
		uart_tx_string("\r\n");
	}
	else
		uart_tx_string("\nError: Invalid command\r\nUsage: #RRGGBBDX (DX: D6, D7, D8)\r\n");
}

int main(void)
{
    SPI_MasterInit();
	uart_init();
	char command[14];
    while (1)
    {
		if (uart_read_command(command, 14))
			process_command(command);
    }
}
