#include "i2c.h"
#include <util/delay.h>

// Fonction pour initialiser les segments du 7 segments en sortie (P1_0 à P1_7)
void init_segments(void)
{
    pca9555_write(PCA9555_CONFIG_PORT0 + 1, 0x00); // Mettre P1_0 à P1_7 en sortie
}

// Fonction pour initialiser les digits en sortie (P0_4 à P0_7)
void init_digits(void)
{
    pca9555_write(PCA9555_CONFIG_PORT0, (~((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)) & 0xFF)); // Mettre P0_4 à P0_7 en sortie
}

// Fonction pour afficher le chiffre "2" sur le digit le plus à droite
void display_digit_2(void)
{
    uint8_t segments = (1 << 0) | (1 << 1) | (1 << 3) | (1 << 4) | (1 << 6); // Segments a, b, d, e, g
    pca9555_write(PCA9555_OUTPUT_PORT0 + 1, segments); // Écrire sur P1_0 à P1_7
    pca9555_write(PCA9555_OUTPUT_PORT0, ~(1 << 4)); // Activer le digit le plus à droite (P0_4)
}

int main(void)
{
    i2c_init();   // Initialisation I2C
    init_segments();  // Configuration des segments en sortie
    init_digits(); // Configuration des digits en sortie

    while (1)
    {
        display_digit_2(); // Afficher le chiffre "2" sur le digit le plus à droite
        _delay_ms(1000);  // Attendre 1 seconde
    }
}
