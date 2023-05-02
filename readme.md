## Jeu Space Invaders
Jeu réalisé dans le cadre du cours de méthodologie de la programmation niveau 2 à l'Université de Lorraine. 

## Installation
Pour installer le jeu, il suffit de cloner le dépôt git et d'ecrire make dans le terminal puis lancer ./space_invaders.

## Doc 
Pour générer la documentation, il suffit d'écrire ```make doc``` dans le terminal. Si ca marque 'doc' is up to date, il faut lancer ```make -B doc```

## Génération de la map
La map est générée aléatoirement grace à un bruit de perlin qui nous permet de faire une carte qui se ressemble mais qui est toujour differente. Pour générer une map, il faut lancer ```make map``` dans le terminal.
J'utilise une librairie qui s'appelle [FastNoiseLite](include/FastNoiseLite.h) pour générer la map. 

## Le système de tir
Le système de tir est assez simple quand on appuie sur espace le vaisseau tire un laser qui varie legerement de droite à gauche pour donner un effet de distortion. Le laser est détruit quand il touche un ennemi ou quand il sort de la map. On peut tirer plusieurs lasers en même temps.

## Les deplacements
Le vaisseau se déplace de gauche à droite. Il peut se déplacer en restant appuyé D (droite) ou Q (gauche). On peut aussi accélérer le vaisseau en appuyant sur Z et ralentir en appuyant sur S. 

