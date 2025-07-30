# Piscine Embarquée 42 - Projets et Exercices

Ce dépôt contient l'ensemble de mes solutions pour les exercices de la **Piscine Embarquée** de l'école 42. L'objectif de cette piscine est d'apprendre les bases de la programmation de systèmes embarqués en langage C, en travaillant directement avec les registres d'un microcontrôleur AVR ATmega328P.

---

## Le Devkit : 42Chips Devboard

Tous les exercices sont réalisés sur une carte de développement custom, la "42Chips Devboard", basée sur un microcontrôleur **ATmega328P**.



#### Composants principaux :
*   **Microcontrôleur** : Atmel ATmega328P (le même que sur un Arduino Uno).
*   **Programmation/Debug** : USB-C via un convertisseur USB-UART CH340G.
*   **GPIOs** :
    *   4 LEDs individuelles (D1-D4).
    *   1 LED RGB (D5).
    *   2 boutons poussoirs (SW1, SW2).
*   **Communication I2C** :
    *   Horloge temps réel (RTC) : PCF8563T.
    *   Capteur de température et d'humidité : AHT20.
    *   Expandeur d'I/O 16-bit : PCA9555PW, contrôlant :
        *   Un afficheur 7 segments à 4 digits.
        *   3 LEDs (D9-D11).
        *   1 bouton poussoir (SW3).
*   **Communication SPI** :
    *   3 LEDs RGB adressables (APA102).
*   **Capteurs Analogiques (ADC)** :
    *   Un potentiomètre (RV1).
    *   Une photorésistance (LDR).
    *   Une thermistance (NTC).

---

## Environnement et Outils Communs

*   **Toolchain** : `avr-gcc` pour la compilation croisée.
*   **Build System** : `make` via des `Makefile`.
*   **Programmation** : `avrdude` est utilisé pour téléverser les fichiers `.hex` sur la mémoire flash du microcontrôleur.
    *   **Programmateur** : `arduino`
    *   **Baudrate** : `115200`

---

## Structure du Dépôt

Le dépôt est organisé en modules, chacun correspondant à un concept clé de la programmation embarquée.

.
├── module00_gpio/
├── module01_timers/
├── module02_uart/
├── module03_rgb_pwm/
├── module04_interrupts/
├── module05_adc/
├── module06_i2c/
├── module07_eeprom/
├── module08_spi/
├── module09_expander_7seg/
└── rush00_multiplayer/


---

## Résumé des Modules

### Module 00 : Premiers Programmes (GPIO)
Introduction aux entrées/sorties de base (GPIO).
- **ex00**: Mise en place du `Makefile` de base pour compiler et flasher.
- **ex01**: Allumer une LED en configurant un port en sortie (`DDRX`, `PORTX`).
- **ex02**: Allumer une LED lorsqu'un bouton est pressé en lisant l'état d'un port (`PINX`).
- **ex03**: Inverser l'état d'une LED à chaque appui (gestion du front montant et de l'anti-rebond).
- **ex04 (Bonus)**: Créer un compteur binaire sur 4 LEDs avec deux boutons (incrément/décrément) en manipulant les bits des registres.

### Module 01 : Timers
Utilisation des timers matériels pour des tâches temporelles sans bloquer le CPU.
- **ex00**: Faire clignoter une LED à 1Hz avec un délai logiciel (busy-waiting).
- **ex01**: Faire clignoter une LED à 1Hz en utilisant le **Timer1** en mode CTC.
- **ex02**: Introduire la **PWM** pour allumer une LED avec un rapport cyclique de 10%.
- **ex03**: Contrôler le rapport cyclique de la PWM avec des boutons.

### Module 02 : Protocole UART
Communication série avec un ordinateur.
- **ex00**: Initialiser l'UART et écrire une fonction pour envoyer un caractère (`uart_tx`).
- **ex01**: Écrire une fonction pour envoyer une chaîne de caractères (`uart_printstr`).
- **ex02**: Écrire une fonction pour recevoir un caractère et le renvoyer en écho (`uart_rx`).
- **ex03**: Utiliser les **interruptions UART** pour un écho qui inverse la casse des caractères.
- **ex04 (Bonus)**: Implémenter un système de login `username`/`password` via l'UART.

### Module 03 : RGB & Timers Avancés
Contrôle de couleurs complexes avec la PWM.
- **ex01**: Faire défiler les couleurs Rouge, Vert, Bleu sur la LED RGB D5.
- **ex02**: Créer une roue de couleurs progressive (arc-en-ciel) en utilisant la PWM sur les 3 canaux de la LED RGB.
- **ex03**: Contrôler la couleur de la LED RGB en envoyant un code couleur hexadécimal (`#RRGGBB`) via l'UART.

### Module 04 : Interruptions
Programmation événementielle pour une meilleure réactivité et efficacité.
- **ex00**: Utiliser une **interruption externe** (liée à un bouton) pour changer l'état d'une LED.
- **ex01**: Utiliser une **interruption de timer** (Timer0) pour faire varier périodiquement le rapport cyclique de la PWM générée par le Timer1.
- **ex02 (Bonus)**: Ré-implémenter le compteur binaire en utilisant uniquement des interruptions pour gérer les boutons et l'affichage.

### Module 05 : Analogique (ADC)
Lecture de signaux analogiques avec le convertisseur analogique-numérique.
- **ex00**: Lire la valeur d'un potentiomètre en 8 bits et l'afficher sur l'UART.
- **ex01**: Lire les valeurs des 3 capteurs analogiques (potentiomètre, LDR, NTC).
- **ex02**: Effectuer les mêmes lectures mais avec la résolution maximale de l'ADC (10 bits).
- **ex03**: Lire la valeur du capteur de température interne du microcontrôleur.
- **ex04 (Bonus)**: Utiliser la valeur du potentiomètre pour contrôler la roue de couleur de la LED RGB et afficher une jauge sur les 4 LEDs.

### Module 06 : Protocole I2C
Communication avec des périphériques sur un bus à 2 fils (SDA/SCL).
- **ex00**: Implémenter les fonctions de base du protocole I2C (`i2c_init`, `i2c_start`, `i2c_stop`).
- **ex01**: Communiquer avec le capteur AHT20 pour lire les données brutes de température et d'humidité.
- **ex02**: Interpréter les données brutes pour afficher des valeurs de température (°C) et d'humidité (%) lisibles.

### Module 07 : EEPROM
Utilisation de la mémoire non-volatile pour stocker des données persistantes.
- **ex00**: Afficher tout le contenu de l'EEPROM au format hexdump.
- **ex01**: Écrire un octet à une adresse spécifique de l'EEPROM.
- **ex02 (Bonus)**: Créer un système de stockage clé-valeur dans l'EEPROM, avec les commandes `WRITE`, `READ`, `FORGET` et `PRINT` via l'UART.

### Module 08 : Protocole SPI
Communication avec des périphériques sur un bus série synchrone (MOSI/MISO/SCK).
- **ex00**: Initialiser le SPI en mode maître pour allumer la première LED RGB APA102.
- **ex01**: Recréer un cycle de couleurs (similaire au Module 03) sur les LEDs SPI.
- **ex02**: Créer un effet visuel "Cylon" (chenillard) sur les 3 LEDs SPI.
- **ex03**: Utiliser le potentiomètre pour contrôler une jauge affichée sur les LEDs SPI.
- **ex04/05 (Bonus)**: Projets plus complexes de contrôle interactif des LEDs SPI.

### Module 09 : Expandeur et 7 Segments
Contrôle de nombreux périphériques (LEDs, afficheur) via un expandeur d'I/O sur le bus I2C.
- **ex00**: Faire clignoter une LED connectée à l'expandeur PCA9555PW.
- **ex01**: Créer un compteur binaire sur les LEDs de l'expandeur.
- **ex02**: Allumer un segment spécifique sur l'afficheur 7-segments.
- **ex03**: Afficher un chiffre et l'incrémenter chaque seconde.
- **ex04**: Afficher "42" en utilisant la technique du **multiplexage temporel**.
- **ex05 (Bonus)**: Créer un compteur de 0 à 9999 sur les 4 digits de l'afficheur.
- **ex06 (Bonus)**: Afficher la valeur du potentiomètre (0-1023) sur l'afficheur.

### Rush 00 : Multiplayer
Projet de groupe pour faire communiquer deux microcontrôleurs via le bus I2C.
- **Objectif**: Créer un jeu de réflexe à deux joueurs.
- **Configuration**: Deux devkits sont connectés en I2C, l'un en mode maître, l'autre en esclave.
- **Gameplay**: Un compte à rebours est affiché sur les LEDs. Le premier joueur qui appuie sur son bouton après la fin du décompte gagne. Appuyer trop tôt fait perdre.

---

## Auteur

**Arthur Duvillaret / aduvilla**
