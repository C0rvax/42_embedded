#include "i2c.h"
#include <util/delay.h>

// Fonction pour initialiser les segments du 7 segments en sortie (P1_0 à P1_7)
void init_segments(void)
{
    pca9555_write(PCA9555_CONFIG_PORT1, 0x00); // Mettre P1_0 à P1_7 en sortie
}

// Fonction pour initialiser les digits en sortie (P0_4 à P0_7)
void init_digits(void)
{
    pca9555_write(PCA9555_CONFIG_PORT0, (~((1 << TOFDP1_PIN) | (1 << TOFDP2_PIN) | (1 << TOFDP3_PIN) | (1 << TOFDP4_PIN)) & 0xFF)); // Mettre P0_4 à P0_7 en sortie
}

void display_digit(uint8_t digit, uint8_t pin)
{
	uint8_t segments;
	switch (digit)
	{
		case 0:
			segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN); // All Segments exept g
			break;
		case 1:
			segments = (1 << TOFB_PIN) | (1 << TOFC_PIN); // Segments a, c
			break;
		case 2:
			segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFG_PIN); // Segments a, b, d, e, g
			break;
		case 3:
			segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFG_PIN); // Segments a, b, c, d, g
			break;
		case 4:
			segments = (1 << TOFF_PIN) | (1 << TOFG_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN); // Segments f, g, c, d
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
			segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN); // All Segments
			break;
		case 9:
			segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFG_PIN); // Segments a, b, d, e, g
			break;
	}
	pca9555_write(PCA9555_OUTPUT_PORT1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_1(uint8_t pin)
{
	uint8_t segments = (1 << TOFB_PIN) | (1 << TOFC_PIN); // Segments a, c
	pca9555_write(PCA9555_OUTPUT_PORT1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_2(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFG_PIN); // Segments a, b, d, e, g
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_3(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFG_PIN); // Segments a, b, c, d, g
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_4(uint8_t pin)
{
	uint8_t segments = (1 << TOFF_PIN) | (1 << TOFG_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN); // Segments f, g, c, d
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_5(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN); // Segments a, f, g, c, d
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_6(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN); // Segments a, c, d, e, f, g
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_7(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN); // Segments a, b, c
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_8(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFC_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFF_PIN) | (1 << TOFG_PIN); // All Segments
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

void display_digit_9(uint8_t pin)
{
	uint8_t segments = (1 << TOFA_PIN) | (1 << TOFB_PIN) | (1 << TOFD_PIN) | (1 << TOFE_PIN) | (1 << TOFG_PIN); // Segments a, b, d, e, g
	pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
	pca9555_write(PCA9555_OUTPUT_PORT0, (uint8_t)~(1 << pin)); // Activer le digit le plus à droite (P0_7)
}

int main(void)
{
	i2c_init();   // Initialisation I2C
	init_segments();  // Configuration des segments en sortie
	init_digits(); // Configuration des digits en sortie

	while (1)
	{
		for (uint8_t i = 0; i < 10; ++i)
			display_digit(i, TOFDP4_PIN);
		_delay_ms(1000);
	}
}
