#ifndef JAMES_HPP
# define JAMES_HPP

#include <avr/eeprom.h>

# define EEPROM_SIZE 1024 // (see section 7.4 p.19)
# define BYTES_LINE 16

void print_hexdump(void);

uint8_t james_read_byte(const uint8_t *addr);

#endif /* __JAMES_HPP__ */
