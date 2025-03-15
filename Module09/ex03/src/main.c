#include "i2c.h"
#include "seven.h"
#include <util/delay.h>

void increment_and_display_digit(uint8_t *digit)
{
    *digit = (*digit + 1) % 10; // Incrémenter et retourner à 0 après 9
    display_digit(*digit, TOFDP4_PIN); // Afficher le chiffre sur le digit le plus à droite
}

int main(void)
{
    i2c_init();   // Initialisation I2C
    init_segments();  // Configuration des segments en sortie
    init_digits(); // Configuration des digits en sortie

    uint8_t digit = 0; // Initialiser le chiffre à 0

    while (1)
    {
        increment_and_display_digit(&digit); // Incrémenter et afficher le chiffre
        _delay_ms(1000); // Attendre une seconde
    }
}
