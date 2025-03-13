#ifndef JAMES_HPP
# define JAMES_HPP

#include <avr/eeprom.h>

# define KEY 0x80 // Key marker
# define VALUE 0x81 // Value marker
# define END 0x82 // End of pair marker
# define EEPROM_SIZE 1024 // (see section 7.4 p.19)
# define BYTES_LINE 16
#define MAX_KEY_SIZE 32
#define MAX_VALUE_SIZE 32
#define MAX_CMD_SIZE 8

void print_hexdump(void);
int strcmp(const char *str1, const char *str2);
void eeprom_forget_pair(const unsigned char *cmd);
void eeprom_read_pair(const unsigned char *cmd);
void eeprom_write_pair(const unsigned char *cmd);
uint16_t eeprom_find_empty(const unsigned char* cmd);
int eeprom_find_key(const unsigned char* key);

#endif /* __JAMES_HPP__ */
