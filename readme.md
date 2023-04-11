## Jeu Space Invaders
Jeu réalisé dans le cadre du cours de méthodologie de la programmation niveau 2 à l'Université de Lorraine. 

## Installation
Pour installer le jeu, il suffit de cloner le dépôt git et d'ecrire make dans le terminal puis lancer ./space_invaders.

## Doc 
Pour générer la documentation, il suffit d'écrire ```make doc``` dans le terminal. Si ca marque 'doc' is up to date, il faut lancer ```make -B doc```

## Génération de la map
La map est générée aléatoirement. Pour générer une map, il faut lancer ```make map``` dans le terminal.
J'utilise une librairie qui s'appelle [FastNoiseLite](include/FastNoiseLite.h) pour générer la map.