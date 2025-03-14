#include "i2c.h"
#include <util/delay.h>


// Fonction pour initialiser la LED D9 en sortie (P0_3)
void init_led(void)
{
   
    pca9555_write(PCA9555_CONFIG_PORT0, (~(1 << D9_PIN) & 0xFF)); // 0b11110111 Mettre P0_3 en sortie (0 = sortie)
}

// Fonction pour faire clignoter la LED
void toggle_led(void)
{
    static uint8_t led_state = 0;

    // Écrire dans le registre de sortie P0 (bit 3)
    if (led_state)
        pca9555_write(PCA9555_OUTPUT_PORT0, (1 << D9_PIN));  // 0b00001000 Éteindre LED (actif bas)
    else
        pca9555_write(PCA9555_OUTPUT_PORT0, 0x00);  // Allumer LED

    led_state = !led_state;
}

int main(void)
{
    i2c_init();   // Initialisation I2C
    init_led();   // Configuration de la LED en sortie

    while (1)
	{
        toggle_led();  // Change l'état de la LED
        _delay_ms(500);  // Pause de 500ms (1 Hz)
    }
}

