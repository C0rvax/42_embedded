#include "i2c.h"
#include "seven.h"
#include <util/delay.h>

int main(void)
{
    i2c_init();   // Initialisation I2C
    init_segments();  // Configuration des segments en sortie
    init_digits(); // Configuration des digits en sortie

    
    while (1) display_number(42); // Afficher "42" sur les digits les plus à droite
}
