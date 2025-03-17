#ifndef SEVEN_H
# define SEVEN_H

# include <avr/io.h>
# include <util/delay.h>

#define TOFA_PIN 0 // Datasheet board
#define TOFB_PIN 1 // Datasheet board
#define TOFC_PIN 2 // Datasheet board
#define TOFD_PIN 3 // Datasheet board
#define TOFE_PIN 4 // Datasheet board
#define TOFF_PIN 5 // Datasheet board
#define TOFG_PIN 6 // Datasheet board
#define TOFDTX_PIN 7 // Datasheet board
#define TOFDP1_PIN 4 // Datasheet board
#define TOFDP2_PIN 5 // Datasheet board
#define TOFDP3_PIN 6 // Datasheet board
#define TOFDP4_PIN 7 // Datasheet board

/**
 * @brief Initialize the segments of the 7-segment display as output.
 */
void init_segments(void);

/**
 * @brief Initialize the digits as output.
 */
void init_digits(void);

/**
 * @brief Clear all digits.
 */
void clear_digits(void);

/**
 * @brief Display a digit on a specific pin.
 * 
 * @param digit The digit to display (0-9).
 * @param pin The pin to activate.
 */
void display_digit(uint8_t digit, uint8_t pin);

/**
 * @brief Display a number on the 7-segment display.
 * 
 * @param number The number to display (0-9999).
 */
void display_number(uint16_t number);

/**
 * @brief Clear all segments.
 */
void clear_segments(void);

#endif /* __SEVEN_H__ */
