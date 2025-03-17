#include "i2c.h"
#include "seven.h"

void init_segments(void)
{
    pca9555_write(PCA9555_CONFIG_PORT1, 0x00); // Set P1_0 to P1_7 as output
}

void init_digits(void)
{
    pca9555_write(PCA9555_CONFIG_PORT0, (~((1 << TOFDP1_PIN) | (1 << TOFDP2_PIN) | (1 << TOFDP3_PIN) | (1 << TOFDP4_PIN)) & 0xFF)); // Set P0_4 to P0_7 as output
}

void clear_digits(void)
{
    pca9555_write(PCA9555_OUTPUT_PORT0, 0xFF); // Turn off all digits
}

void clear_segments(void)
{
    pca9555_write(PCA9555_OUTPUT_PORT1, 0x00); // Turn off all segments
}

void display_digit(uint8_t digit, uint8_t pin)
{
    uint8_t segments;
    switch (digit)
    {
        case 0:
            segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN); // All segments except g
            break;
        case 1:
            segments = (1 << TOFB_PIN) | (1 << TOFC_PIN); // Segments b, c
            break;
        case 2:
            segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFG_PIN); // Segments a, b, d, e, g
            break;
        case 3:
            segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFG_PIN); // Segments a, b, c, d, g
            break;
        case 4:
            segments = (1 << TOFF_PIN) | (1 << TOFG_PIN) | (1 << TOFC_PIN) | (1 << TOFB_PIN); // Segments f, g, c, b
            break;
        case 5:
            segments = (1 << TOFA_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN); // Segments a, f, g, c, d
            break;
        case 6:
            segments = (1 << TOFA_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN); // Segments a, c, d, e, f, g
            break;
        case 7:
            segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN); // Segments a, b, c
            break;
        case 8:
            segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN); // All segments
            break;
        case 9:
            segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN); // Segments a, b, c, d, f, g
            break;
		default:
			segments = 0;
			break;
    }
    clear_segments(); // Turn off all segments before displaying the digit
    pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activate the specified digit
    _delay_ms(1); // Delay to ensure segments are off
    pca9555_write(PCA9555_OUTPUT_PORT1, segments); // Write to P1_0 to P1_7
    clear_digits(); // Turn off all digits
    pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activate the specified digit
}

void display_number(uint16_t number)
{
    uint8_t thousands = number / 1000;
    uint8_t hundreds = (number / 100) % 10;
    uint8_t tens = (number / 10) % 10;
    uint8_t units = number % 10;

    // Display thousands on the first digit from the left
    display_digit(thousands, TOFDP1_PIN);
    _delay_ms(2); // Small delay to avoid flickering

    // Display hundreds on the second digit from the left
    display_digit(hundreds, TOFDP2_PIN);
    _delay_ms(2); // Small delay to avoid flickering
	
    // Display tens on the third digit from the left
    display_digit(tens, TOFDP3_PIN);
    _delay_ms(2); // Small delay to avoid flickering

    // Display units on the rightmost digit
    display_digit(units, TOFDP4_PIN);
    _delay_ms(2); // Small delay to avoid flickering
}
