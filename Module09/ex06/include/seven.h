#ifndef SEVEN_H
# define SEVEN_H

# include <avr/io.h>
# include <util/delay.h>

#define TOFA_PIN 0 // datasheet board
#define TOFB_PIN 1 // datasheet board
#define TOFC_PIN 2 // datasheet board
#define TOFD_PIN 3 // datasheet board
#define TOFE_PIN 4 // datasheet board
#define TOFF_PIN 5 // datasheet board
#define TOFG_PIN 6 // datasheet board
#define TOFDTX_PIN 7 // datasheet board
#define TOFDP1_PIN 4 // datasheet board
#define TOFDP2_PIN 5 // datasheet board
#define TOFDP3_PIN 6 // datasheet board
#define TOFDP4_PIN 7 // datasheet board

void init_segments(void);
void init_digits(void);
void clear_digits(void);
void display_digit(uint8_t digit, uint8_t pin);
void display_number(uint16_t number);
void clear_segments(void);

#endif /* __SEVEN_H__ */
