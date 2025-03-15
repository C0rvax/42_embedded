#include "i2c.h"
#include <util/delay.h>

// Fonction pour initialiser les LEDs D9, D10, D11 en sortie (P0_3, P0_2, P0_1)
void init_leds(void)
{
    pca9555_write(PCA9555_CONFIG_PORT0, (~((1 << D9_PIN) | (1 << D10_PIN) | (1 << D11_PIN)) & 0xFF)); // Mettre P0_3, P0_2, P0_1 en sortie
    pca9555_write(PCA9555_OUTPUT_PORT0, 0x07); // Éteindre les LEDs D9, D10, D11
}

// Fonction pour initialiser le bouton SW3 en entrée (P0_0)
void init_button(void)
{
    pca9555_write(PCA9555_CONFIG_PORT0, (1 << SW3_PIN) | (~((1 << D9_PIN) | (1 << D10_PIN) | (1 << D11_PIN)) & 0xFF)); // Mettre P0_0 en entrée
}

// Fonction pour lire l'état du bouton SW3
uint8_t read_button(void)
{
    return !(pca9555_read(PCA9555_INPUT_PORT0) & (1 << SW3_PIN)); // Bouton actif bas
}

// Fonction pour afficher la valeur du compteur sur les LEDs
void display_counter(uint8_t counter)
{
    uint8_t led_output = 0;
    if (counter & 0x01) led_output |= (1 << D9_PIN);  // Allume D9 si le bit 0 est 1
    if (counter & 0x02) led_output |= (1 << D10_PIN); // Allume D10 si le bit 1 est 1
    if (counter & 0x04) led_output |= (1 << D11_PIN); // Allume D11 si le bit 2 est 1
    pca9555_write(PCA9555_OUTPUT_PORT0, led_output);
}

int main(void)
{
    uint8_t counter = 7;
    uint8_t button_pressed = 0;

    i2c_init();   // Initialisation I2C
    init_leds();  // Configuration des LEDs en sortie
    init_button(); // Configuration du bouton en entrée
    display_counter(counter); // Éteindre toutes les LEDs au démarrage

    while (1)
    {
        if (read_button())
        {
            if (!button_pressed)
            {
                counter--;
                display_counter(counter);
				if (counter == 0)
					counter = 8;
                button_pressed = 1;
            }
        }
        else
        {
            button_pressed = 0;
        }
        _delay_ms(50);  // Anti-rebond
    }
}

