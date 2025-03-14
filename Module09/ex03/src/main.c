#include "i2c.h"
#include <stdint.h>
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

	display_digit_2(TOFDP4_PIN); // Afficher le chiffre "2" sur le digit le plus à droite
    while (1);
}
