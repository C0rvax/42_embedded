#include "james.h"
#include "prog.h"

uint8_t james_read_byte(const uint8_t *addr)
{
    while (EECR & (1 << EEPE)); // Wait for completion of previous write
    EEAR = (uint16_t)addr; // Set up address register
    EECR |= (1 << EERE); // Start eeprom read by writing EERE
    return EEDR; // Return data from data register
}

void james_write_byte(uint8_t *addr, uint8_t value)
{
    while (EECR & (1 << EEPE)); // Wait for completion of previous write
    EEAR = (uint16_t)addr; // Set up address register
    EEDR = value; // Set up data register
    EECR |= (1 << EEMPE); // Write logical one to EEMPE
    EECR |= (1 << EEPE); // Start eeprom write by setting EEPE
}

void print_hexdump(void)
{
    for (uint16_t i = 0; i < EEPROM_SIZE; i += BYTES_LINE)
	{
		uart_tx_string("0000");
		uart_print_hex16(i);
        uart_tx_string(" ");
        for (uint8_t j = 0; j < BYTES_LINE; j++)
		{
            if (i + j < EEPROM_SIZE)
			{
                uint8_t val = james_read_byte((uint8_t *)(i + j));
				uart_print_hex8(val);
				if (j % 2)
					uart_tx(' ');
            }
			else
                uart_tx_string("   ");
        }
        uart_tx_string(" |");
        for (uint8_t j = 0; j < BYTES_LINE; j++)
        {
            if (i + j < EEPROM_SIZE)
            {
                uint8_t val = james_read_byte((uint8_t *)(i + j));
                if (val >= 32 && val <= 126)
                    uart_tx(val);
                else
                    uart_tx('.');
            }
            else
                uart_tx(' ');
        }
        uart_tx_string("|\r\n");
    }
}

// Function to find a key in the EEPROM
int eeprom_find_key(const unsigned char* key)
{
    uint16_t i = 0;
    char eeprom_key[MAX_KEY_SIZE];
    
    while (i < EEPROM_SIZE)
    {
        if (james_read_byte((void *)i) == KEY)
        {
            i++;
            uint16_t j = 0;
            // Read the key from EEPROM
            while (i < EEPROM_SIZE && james_read_byte((void *)i) != VALUE && j < MAX_KEY_SIZE - 1)
                eeprom_key[j++] = james_read_byte((void *)i++);
            eeprom_key[j] = '\0';
            // Compare the key with the given key
            if (strcmp(eeprom_key, (const char*)key) == 0)
                return i - j - 1;
        }
        i++;
    }
    return 2000; // Key not found
}

// Function to find an empty space in the EEPROM
uint16_t eeprom_find_empty(const unsigned char* cmd)
{
    uint8_t size = 0;
    while (cmd[size] != '\0') size++;
    size += 1; // Add space for END marker

    uint16_t i = 0;
    uint16_t free_space_start = 0;
    uint16_t free_space_length = 0;

    while (i < EEPROM_SIZE)
    {
        uint8_t byte = james_read_byte((void *)i);
        if (byte != KEY && byte != VALUE && byte != END)
        {
            if (free_space_length == 0)
                free_space_start = i;
            free_space_length++;
            if (free_space_length >= size)
                return free_space_start;
        }
        else
            free_space_length = 0;
        i++;
    }
    return 2000; // No free space
}

// Function to write a key/value pair to the EEPROM
void eeprom_write_pair(const unsigned char *cmd)
{
    uint16_t addr;
    uint16_t addr_start;
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
    uint16_t i = 0, j = 0;

    // Extract key and value from cmd
    while (cmd[i] != KEY && cmd[i] != '\0') i++;
    if (cmd[i] == '\0') return;
    i++;
    while (cmd[i] != VALUE && cmd[i] != '\0' && j < MAX_KEY_SIZE - 1) key[j++] = cmd[i++];
    key[j] = '\0';
    if (cmd[i] == '\0') return;
    i++;
    j = 0;
    while (cmd[i] != '\0' && j < MAX_VALUE_SIZE - 1) value[j++] = cmd[i++];
    value[j] = '\0';

    // Check if the key already exists
    if (eeprom_find_key((const unsigned char*)key) != 2000)
    {
        uart_tx_string("already exists\r\n");
        return;
    }

    // Find a free space
    addr_start = eeprom_find_empty(cmd);
    addr = addr_start;
    if (addr == 2000)
    {
        uart_tx_string("no space left\r\n");
        return;
    }

    // Write the key/value pair
    james_write_byte((void *)addr++, KEY);
    for (i = 0; key[i] != '\0'; i++)
        james_write_byte((void *)addr++, key[i]);
    james_write_byte((void *)addr++, VALUE);
    for (i = 0; value[i] != '\0'; i++)
        james_write_byte((void *)addr++, value[i]);
    james_write_byte((void *)addr, END); // End marker

    // Display the address where the pair is stored
    uart_tx_string("Stored at: 0x");
    uart_print_hex16(addr);
    uart_tx_string("\r\n");
}

// Function to read a value from a key
void eeprom_read_pair(const unsigned char *cmd)
{
    uint16_t addr;
    char key[MAX_KEY_SIZE];
    uint16_t i = 0, j = 0;

    // Extract key from cmd
    while (cmd[i] != KEY && cmd[i] != '\0') i++;
    if (cmd[i] == '\0') return;
    i++;
    while (cmd[i] != VALUE && cmd[i] != '\0' && j < MAX_KEY_SIZE - 1) key[j++] = cmd[i++];
    key[j] = '\0';

    addr = eeprom_find_key((const unsigned char*)key);
    if (addr != 2000)
    {
        // Find the value in EEPROM
        while (james_read_byte((void *)addr) != VALUE) addr++;
        addr++;
        // Read and print the value
        while (james_read_byte((void *)addr) != END && addr < EEPROM_SIZE)
            uart_tx(james_read_byte((void *)addr++));
    } 
    else
        uart_tx_string("empty\r\n");
}

// Function to delete a key
void eeprom_forget_pair(const unsigned char *cmd)
{
    uint16_t addr;
    char key[MAX_KEY_SIZE];
    uint16_t i = 0, j = 0;

    // Extract key from cmd
    while (cmd[i] != KEY && cmd[i] != '\0') i++;
    if (cmd[i] == '\0') return;
    i++;
    while (cmd[i] != VALUE && cmd[i] != '\0' && j < MAX_KEY_SIZE - 1) key[j++] = cmd[i++];
    key[j] = '\0';

    addr = eeprom_find_key((const unsigned char*)key);
    if (addr != 2000)
    {
        // Erase the entire pair
        while (james_read_byte((void *)addr) != END)
            james_write_byte((void *)addr++, 0x00);
        james_write_byte((void *)addr, 0x00); // Erase the end marker
        uart_tx_string("deleted\r\n");
    }
    else
        uart_tx_string("not found\n");
}
