#ifndef JAMES_HPP
# define JAMES_HPP

#include <avr/eeprom.h>

# define KEY 0x80 // Key marker
# define VALUE 0x81 // Value marker
# define END 0x82 // End of pair marker
# define EEPROM_SIZE 1024 // EEPROM size
# define BYTES_LINE 16
#define MAX_KEY_SIZE 32
#define MAX_VALUE_SIZE 32
#define MAX_CMD_SIZE 8

/**
 * @brief Print a hexdump of the EEPROM.
 */
void print_hexdump(void);

/**
 * @brief Write a byte to the EEPROM.
 * 
 * @param addr The address to write to.
 * @param value The value to write.
 */
void james_write_byte(uint8_t *addr, uint8_t value);

/**
 * @brief Read a byte from the EEPROM.
 * 
 * @param addr The address to read from.
 * @return The read value.
 */
uint8_t james_read_byte(const uint8_t *addr);

/**
 * @brief Compare two strings.
 * 
 * @param str1 The first string.
 * @param str2 The second string.
 * @return 0 if the strings are equal, non-zero otherwise.
 */
int strcmp(const char *str1, const char *str2);

/**
 * @brief Forget a key/value pair in the EEPROM.
 * 
 * @param cmd The command containing the key.
 */
void eeprom_forget_pair(const unsigned char *cmd);

/**
 * @brief Read a key/value pair from the EEPROM.
 * 
 * @param cmd The command containing the key.
 */
void eeprom_read_pair(const unsigned char *cmd);

/**
 * @brief Write a key/value pair to the EEPROM.
 * 
 * @param cmd The command containing the key and value.
 */
void eeprom_write_pair(const unsigned char *cmd);

/**
 * @brief Find an empty space in the EEPROM.
 * 
 * @param cmd The command to find space for.
 * @return The address of the empty space.
 */
uint16_t eeprom_find_empty(const unsigned char* cmd);

/**
 * @brief Find a key in the EEPROM.
 * 
 * @param key The key to find.
 * @return The address of the key, or 2000 if not found.
 */
int eeprom_find_key(const unsigned char* key);

#endif /* __JAMES_HPP__ */
