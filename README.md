PROJET 1 : SYSTÈME DE FICHIERS SIMPLIFIÉ EN C

IDENTIFICATION

Étudiant : Merlin Goyet
Projet réalisé seul.
Projet choisi : création d'un système de fichiers simplifié.
Dépôt GitHub : https://github.com/Merlin-mp2i/Projet-1-MerlinGohier
Date du dernier commit : à compléter juste avant le rendu.

PRÉSENTATION

Le but du projet est de créer un petit système de fichiers qui fonctionne dans la mémoire de l'ordinateur. Le programme ne crée pas de vrais fichiers sur le disque. Il simule des fichiers et des dossiers pendant son exécution.

Le programme permet de créer un dossier avec mkdir, de créer un fichier avec touch, d'afficher le contenu d'un dossier avec ls, de se déplacer avec cd, d'écrire et de lire un fichier avec write, append et read, de supprimer avec del, d'afficher l'arborescence avec arbo et de connaître l'espace utilisé avec space.

ANALYSE ET CONCEPTION

Un fichier possède un nom, un contenu et un dossier parent. Un dossier possède un nom, un dossier parent, une liste de fichiers et une liste de sous-dossiers. Ces structures permettent de créer une arborescence comme dans un vrai ordinateur.

Le système de fichiers possède un pointeur vers le dossier racine et un pointeur vers le dossier dans lequel l'utilisateur se trouve.

Le fichier main.c lit les commandes de l'utilisateur. Le fichier src/dossier.c contient les fonctions liées aux dossiers. Le fichier src/fichier.c contient les fonctions liées aux fichiers. Le fichier src/filesysteme.c gère l'initialisation, les déplacements et le calcul de l'espace. Le fichier include/filesytem.h contient les structures et les prototypes des fonctions.

DÉMARCHE DE RÉALISATION

J'ai d'abord créé les structures Fichier, dossier et Filesystem. J'ai ensuite créé les fonctions pour créer, afficher et supprimer les dossiers et les fichiers. Puis j'ai ajouté les fonctions permettant d'écrire, de lire et d'ajouter du texte dans un fichier.

Après cela, j'ai programmé les déplacements dans l'arborescence. La commande cd permet d'entrer dans un sous-dossier. La commande cd .. permet de remonter dans le dossier parent. Un chemin commençant par / part du dossier racine.

Enfin, j'ai créé l'interface dans main.c afin que l'utilisateur puisse saisir les commandes. J'ai testé les commandes principales avec le fichier tests/test_commands.txt.

Une difficulté était de garder l'arborescence correcte après une suppression. Lorsqu'un fichier ou un dossier est supprimé, il faut libérer sa mémoire et décaler les éléments suivants dans le tableau.

COMPILATION ET LANCEMENT

Dans un terminal placé à la racine du projet, taper :

gcc main.c src/dossier.c src/fichier.c src/filesysteme.c -o filesystem.exe

Puis taper :

./filesystem.exe

EXEMPLE D'UTILISATION

mkdir cours
cd cours
touch note
write note Bonjour MP2I
read note
append note !
read note
cd ..
arbo
exit

TESTS

Le fichier tests/test_commands.txt contient des commandes simples à taper dans le programme. Elles vérifient la création de dossiers et de fichiers, l'écriture, la lecture, l'ajout de texte, les déplacements, la suppression, l'espace utilisé et quelques erreurs simples.

LIMITES ET AMÉLIORATIONS POSSIBLES

Les données sont conservées seulement pendant l'exécution du programme : elles ne sont pas enregistrées sur le disque. Une amélioration possible serait de sauvegarder l'arborescence dans un vrai fichier. On pourrait aussi ajouter le renommage, la copie et le déplacement de fichiers.

RÉPARTITION DU TRAVAIL ET BILAN INDIVIDUEL

Le projet a été réalisé seul par Merlin Goyet. J'ai réalisé les structures de données, les fonctions sur les fichiers et les dossiers, les déplacements, l'interface en ligne de commande, les tests et ce README.

La principale difficulté a été la gestion des tableaux dynamiques et des suppressions dans l'arborescence. Ce projet m'a permis de mieux comprendre les structures, les pointeurs, l'allocation dynamique et la gestion de la mémoire en C.
