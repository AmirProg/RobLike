# Equipe

- CHALI Amir
- BARBAROUX Leo-Paul

# Encadrant

- CONINX Alex

# Liste des bibliothèques

- SFML
- Des bouts de codes tirés de "All Mighty" (mini moteur de jeu en C++ avec SFML crée par Amir)
-> Les codes de ce moteur sont disponibles sur le github de Amir (lien plus bas)

# Comment compiler

Assurez-vous de tout avoir dans un même dossier (par exemple, dossier sources), codes sources et ressources (images...)
Puis :
1 - make
2 - ./roblike -> lance le jeu

# Comment jouer, but du jeu

RobLike est un jeu de type Rogue-Like. Vous contrôlez deux personnages en multijoueur sur la même plateforme
Vous pouvez déplacer le premier avec les touches ZQSD (Z = haut, Q = gauche, S = bas, D = droite) et le second avec les touches OKLM (O = haut, K = gauche, L = bas, M = droite)
Pour tirer avec le premier persnnage : touche A, avec le second : touche P

L'objectif est de tuer les monstres sur la map avant de pouvoir changer de niveau. Une fois tous les monstres tués, vous pouvez changer de niveau en allant tout en haut de la fenêtre (la petite ouverture entre les tuiles solides).

Vous pouvez tomber sur une "Item Room", une salle qui se présente toujours avec deux coffres que vous pouvez ramasser. Cela vous donne un item aléatoire parmi tous les items du jeu.
Les items peuvent être actifs ou passifs, les passifs augmentent les stats du personnage, les actifs peuvent agir directement sur les projectiles que vous envoyez.
Un même joueur peut amasser tout le butin (les deux items), mais on conseille de partager, chacun son coffre c'est moins cruel...

Peu de niveaux sont disponibles actuelement (3), le jeu se finit donc très vite... Vous resterez bloqués sur le dernier niveau après avoir tué les monstres.
Si l'un des deux joueurs meurt (points de vie à 0), c'est Game Over.

Le jeu n'est donc pas très complet pour le moment mais la base semble très solide et permettrait de continuer le jeu sans souci.

# Conception du programme

- Le projet est composé de 17 classes :

* Animation
* Entity (abstraite)
* Player
* Map (abstraite)
* TileMap
* NonCopyable (les objets qui n'auraient aucun sens à être copiés)
* Menu
* Game
* Monster
* Matrix
* TileMapProperties
* Item (abstraite)
* PassiveItem
* ActiveItem
* Floor
* Projectile
* Collidable (interface)

Les collisions sont gérés avec des fonctions statiques templates dans un fichier .hpp (collision.hpp)

Nous avons essayés de lier toutes ces classes entre-elles. Cette articulation se fait principalement au sein de la classe Game.

Le principal souci du jeu est l'adaptation du code. Un jeu correctement conçu pour être générique devrait permettre de changer le moteur graphique aisément (passage de la 2D à la 3D par exemple), sans ne jamais avoir à toucher aux autres aspects techniques des classes.

La plupart des objets qui sont affichables héritent directement de la classe abstraite sf::Drawable.

Néanmoins le code est très générique pour ce qui est de la 2D. Il est très simple d'ajouter de nouveaux items et effets d'items (pointeurs de fonctions enveloppés dans des objets std::function de C++11). Les maps sont récupérés automatiquement à partir de fichiers textes (voir exemple dans les sources avec level1.txt). Puis, les propriétés de chaque tuiles (donc la logique interne du jeu) est séparée du côté graphique de la classe TileMap avec la classe TileMapProperties qui défini la logique du jeu (ce qui est solide, ce qui ne l'est pas, ce qui est un item, ce qui ne l'est pas...)

Il est très simple d'ajouter des nouveaux niveaux, monstres et items. Tous ces éléments viennent s'ajouter automatiquement dans la logique du jeu qui se poursuit naturellement.

L'intelligence artificielle pour les monstres est très basique : une énumération permet de définir l'intelligence à fournir au monstre qui pour le moment peut être de type chasseur ou fuyard (chasseur va détecter la cible la plus proche entre les deux joueurs et la poursuivre, fuyard va dans le sens opposé au joueur le plus proche).

# Points négatifs, bugs notables

- Le manque de séparation graphique/technique sur de nombreux objets (player, monstre...)
- Une IA pas très développée pour les monstres, il est regrettable de ne pas avoir également mis les deux classes monstres concrètes que nous souhaitions voir implémentées (MonsterShooter, MonsterMelee). 

- L'IA pour le joueur 2 n'est pas implémentée, c'est dommage. Mais le principe aurait été sensiblement identique aux monstres. Une classe AI aurait été intéressante pour tout organiser correctement.

- Un bug que nous n'avons pas réussi à corriger malgré toutes nos tentatives intervient suivant l'ordre où les monstres sont tués. Si le premier du tableau est tué tous les autres sont supprimés également du tableau.

- Le menu n'est pas très fluide, et si le joueur reste trop longtemps sur le menu le jeu crash.

- Les collisions pourraient être largement améliorées, la méthode actuelle laisse des écarts grossiers

- La façon d'intégrer les monstres dans les niveaux est à revoir. On devrait encapsuler la map et les monstres présents dans une classe Level plutôt que de faire des conditions à chaque fois pour savoir les monstres à intégrer au niveau actuel.

# Séparation du travail

Nous avons fonctionné de la façon suivante : on écrivait chacun des classes différentes et on mettait le tout en commun et on essayait de réadapter le code pour accueillir les différentes classes. Nous voulions utiliser github pour nous organiser, mais finalement nous avons préféré travailler de notre côté et nous envoyer les codes.

Chacun a travaillé un minimum sur chaque classe. Lorsqu'un membre de l'équipe avait fini sa classe et l'envoyait, l'autre devait de toutes façons modifier pour qu'elle soit adaptée avec ce qu'il avait déjà modifié.

La logique du jeu et la façon d'y parvenir sont encore une fois le fruit d'une concertation d'équipe.

# GITHUB :



