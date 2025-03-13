#include "james.h"
#include "prog.h"

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

void	ft_bzero(void* s, uint8_t n)
{
	if (s == NULL || n == 0)
		return;
	char* buf;
	for (uint8_t i = 0; i < n; ++i)
		buf[i] = '\0';
	s = (void*)buf;
}

// Function to determine which command is given
uint8_t which_command(unsigned char* cmd)
{
    char command[MAX_CMD_SIZE];
    int i = 0;

    // Extract command until KEY or end of cmd
    while (cmd[i] != '\0' && cmd[i] != KEY && i < MAX_KEY_SIZE - 1)
	{
		command[i] = cmd[i];
		i++;
	}
    command[i] = '\0';

    // Compare extracted command to known commands
    if (strcmp(command, "READ") == 0)
        return 1;
    else if (strcmp(command, "WRITE") == 0)
        return 2;
    else if (strcmp(command, "FORGET") == 0)
        return 3;
    else if (strcmp(command, "PRINT") == 0)
        return 4;
    else
        return 0; // Invalid command
}

// Function to validate a command
uint8_t is_valid_cmd(unsigned char* cmd)
{
    uint8_t i = 0;
    uint8_t key_len = 0;
    uint8_t value_len = 0;

    if (cmd[0] == KEY)
        return 0; // Empty command
    // Find KEY
    while (cmd[i] != KEY)
    {
        if (cmd[i] == '\0' || i >= MAX_CMD_SIZE - 1)
            return 0; // KEY not found
        i++;
    }
    i++; // Move past KEY

    // Count characters between KEY and VALUE
    while (cmd[i] != VALUE)
    {
        if (cmd[i] == '\0' || key_len >= MAX_KEY_SIZE)
            return 0; // VALUE not found or key too long
        key_len++;
        i++;
    }
    i++; // Move past VALUE

    // Count characters after VALUE
    while (cmd[i] != '\0')
    {
        if (value_len >= MAX_VALUE_SIZE)
            return 0; // value too long
        value_len++;
        i++;
    }

    // Ensure key and value lengths are within bounds
    if (key_len < 1 || key_len > MAX_KEY_SIZE || value_len < 1 || value_len > MAX_VALUE_SIZE)
        return 0;

    return 1;
}

int main(void)
{
    uart_init();
    uart_tx_string("EEPROM CLI Ready!\r\n\r\n");

    unsigned char command[72];
	ft_bzero(command, 72);

    while (1)
	{
        uart_rx_string(command, sizeof(command));
		uint8_t cmd = which_command(command);
		switch (cmd)
		{
			case 0:
                uart_tx_string("\r\n");
                uart_tx_string("Invalid command\r\n");
                break;
            case 1:
                uart_tx_string("\r\n");
                eeprom_read_pair(command);
				uart_tx_string("\r\n");
                break;
            case 2:
                uart_tx_string("\r\n");
                if (is_valid_cmd(command))
					eeprom_write_pair(command);
                break;
            case 3:
                uart_tx_string("\r\n");
                eeprom_forget_pair(command);
                break;
            case 4:
                uart_tx_string("\r\n");
                print_hexdump();
                break;
            default:
                break;
		}
        ft_bzero(command, 72);
    }
}

