![42 School](https://img.shields.io/badge/École_42-Piscine_Embarquée-black?style=for-the-badge&logo=42)

# Piscine Embarquée - Cursus de Programmation sur ATmega328P

Bienvenue dans le dépôt de ma Piscine Embarquée !

Ce repository centralise l'ensemble de mes solutions aux projets de la Piscine Embarquée de 42. L'objectif est d'acquérir des compétences fondamentales en programmation de systèmes embarqués en C, en interagissant directement avec les registres d'un microcontrôleur **AVR ATmega328P** sur une carte de développement custom.

Chaque module représente un défi technique, de la simple manipulation de GPIO à la gestion de protocoles de communication complexes comme I2C et SPI.

## 📚 Table des Matières

1.  [Le Devkit : 42Chips Devboard](#le-devkit--42chips-devboard)
2.  [Environnement et Outils](#environnement-et-outils)
3.  [Structure du Dépôt](#structure-du-dépôt)
4.  [Détail des Modules](#détail-des-modules)
    - [Module 00 : GPIO](#module-00--premiers-programmes-gpio)
    - [Module 01 : Timers](#module-01--timers)
    - [Module 02 : UART](#module-02--protocole-uart)
    - [Module 03 : RGB & PWM](#module-03--rgb--timers-avancés)
    - [Module 04 : Interruptions](#module-04--interruptions)
    - [Module 05 : ADC](#module-05--analogique-adc)
    - [Module 06 : I2C](#module-06--protocole-i2c)
    - [Module 07 : EEPROM](#module-07--eeprom)
    - [Module 08 : SPI](#module-08--protocole-spi)
    - [Module 09 : Expandeur & 7 Segments](#module-09--expandeur-et-7-segments)
    - [Rush 00 : Multiplayer](#rush-00--multiplayer)
5.  [Auteur](#auteur)

---

## Le Devkit : 42Chips Devboard

Tous les exercices sont réalisés sur la carte de développement **42Chips Devboard**, basée sur un microcontrôleur **ATmega328P**.

![Schéma Devboard](https://github.com/C0rvax/embeded/blob/main/elec42_pool.jpg?raw=true)

#### Composants principaux :
*   **Microcontrôleur** : Atmel ATmega328P (le même que sur un Arduino Uno).
*   **Programmation/Debug** : USB-C via un convertisseur USB-UART CH340G.
*   **GPIOs** : 4 LEDs, 1 LED RGB, 2 boutons poussoirs.
*   **Communication I2C** : RTC, capteur Temp/Humidité, Expandeur d'I/O 16-bit (contrôlant un afficheur 7 segments, 3 LEDs, 1 bouton).
*   **Communication SPI** : 3 LEDs RGB adressables (APA102).
*   **Capteurs Analogiques (ADC)** : Potentiomètre, LDR, NTC.

---

## Environnement et Outils

![C](https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge&logo=c)
![Makefile](https://img.shields.io/badge/Build-Makefile-lightgrey.svg?style=for-the-badge&logo=gnu-make)
![AVR](https://img.shields.io/badge/Toolchain-AVR--GCC-orange.svg?style=for-the-badge)

*   **Toolchain** : `avr-gcc` pour la compilation croisée.
*   **Build System** : `make` via des `Makefile`.
*   **Programmation** : `avrdude` est utilisé pour téléverser les fichiers `.hex`.
    *   **Programmateur** : `arduino`
    *   **Baudrate** : `115200`

---

## Structure du Dépôt

Le dépôt est organisé en modules, chacun correspondant à un concept clé de la programmation embarquée.

```text
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
```

---

## Détail des Modules

### Module 00 : Premiers Programmes (GPIO)
*   **Description** : Introduction aux entrées/sorties de base (GPIO).
*   **Compétences acquises** : Configuration des registres `DDRX` (direction), `PORTX` (sortie) et `PINX` (entrée). Gestion de l'état des broches, lecture de boutons, et manipulation binaire de base.

### Module 01 : Timers
*   **Description** : Utilisation des timers matériels pour des tâches temporelles et la génération de signaux PWM, sans bloquer le CPU.
*   **Compétences acquises** : Configuration des timers en mode CTC, calcul de prescalers, génération de signaux PWM (Pulse-Width Modulation), contrôle de rapport cyclique.

### Module 02 : Protocole UART
*   **Description** : Mise en place de la communication série pour échanger des données avec un ordinateur.
*   **Compétences acquises** : Configuration du protocole UART, envoi et réception de caractères et de chaînes, utilisation des interruptions UART pour une communication non-bloquante.

### Module 03 : RGB & Timers Avancés
*   **Description** : Contrôle de couleurs complexes sur une LED RGB en utilisant la PWM.
*   **Compétences acquises** : Génération de multiples signaux PWM pour contrôler les canaux R, G et B. Création de transitions de couleurs douces et contrôle interactif via l'UART.

### Module 04 : Interruptions
*   **Description** : Programmation événementielle pour une meilleure réactivité et une meilleure efficacité du CPU.
*   **Compétences acquises** : Gestion des interruptions externes (liées aux boutons) et des interruptions de timers. Conception de programmes réactifs sans boucle `while(1)` vide.

### Module 05 : Analogique (ADC)
*   **Description** : Lecture de signaux analogiques (tensions variables) à l'aide du convertisseur analogique-numérique.
*   **Compétences acquises** : Configuration de l'ADC, lecture de capteurs analogiques (potentiomètre, photorésistance), gestion de la résolution (8-bit vs 10-bit).

### Module 06 : Protocole I2C
*   **Description** : Communication avec des périphériques complexes sur un bus à 2 fils (SDA/SCL).
*   **Compétences acquises** : Implémentation du protocole I2C (maître), communication avec des capteurs externes (AHT20), lecture et interprétation de fiches techniques (datasheets) pour le formatage des données.

### Module 07 : EEPROM
*   **Description** : Utilisation de la mémoire non-volatile pour stocker des données persistantes qui survivent à un redémarrage.
*   **Compétences acquises** : Lecture et écriture dans l'EEPROM. Implémentation d'un système de stockage clé-valeur persistant.

### Module 08 : Protocole SPI
*   **Description** : Communication avec des périphériques sur un bus série synchrone rapide.
*   **Compétences acquises** : Configuration du SPI en mode maître. Contrôle de périphériques en chaîne (daisy-chaining) comme les LEDs adressables APA102.

### Module 09 : Expandeur et 7 Segments
*   **Description** : Augmenter le nombre de GPIOs en utilisant un expandeur I2C pour contrôler un afficheur 7-segments.
*   **Compétences acquises** : Contrôle d'un expandeur d'I/O (PCA9555PW). Implémentation du multiplexage temporel pour afficher plusieurs chiffres sur un seul afficheur.

### Rush 00 : Multiplayer
![I2C](https://img.shields.io/badge/Tech-I2C_Multi--Master-blueviolet.svg?style=for-the-badge)
*   **Description** : Projet de groupe pour faire communiquer deux microcontrôleurs et créer un jeu.
*   **Objectif** : Créer un jeu de réflexe à deux joueurs où les deux devkits communiquent via le bus I2C.
*   **Compétences Clés** : Communication I2C entre deux microcontrôleurs (un maître, un esclave), synchronisation, gestion d'un protocole de jeu simple.

---

## Auteur

*   **Arthur Duvillaret**
*   **Login 42** : `aduvilla`
*   **GitHub** : [@C0rvax](https://github.com/C0rvax)
*   **LinkedIn** : [Arthur Duvillaret](https://www.linkedin.com/in/arthur-duvillaret-427912377/)
