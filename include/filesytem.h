#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max 50
#define ESPACE_TOTAL 10000

/* Un dossier peut contenir d'autres dossiers et des fichiers. */
typedef struct dossier dossier;

typedef struct Fichier{
    char *name;          /* Nom du fichier. */
    char *content;       /* Texte contenu dans le fichier. */
    size_t taille;       /* Nombre de caracteres du contenu. */
    dossier *parent;     /* Dossier qui contient ce fichier. */
} Fichier;

struct dossier
{
    char *name;          /* Nom du dossier. */
    dossier *parent;     /* NULL pour la racine. */
    Fichier **files;     /* Tableau de fichiers. */
    int fn;              /* Nombre de fichiers. */
    dossier **next;      /* Tableau de sous-dossiers. */
    int fd;              /* Nombre de sous-dossiers. */
};

typedef struct
{
    dossier *root;
    dossier *current;
    size_t espace_total; /* Capacite maximale du systeme. */
} Filesystem;

/* Dossiers */
bool est_vide_dossier_d(dossier *p);
bool est_vide_dossier_f(dossier *p);
int indice_dossier(dossier *parent, const char *nom);
void suprimer_dossier(dossier *parent, const char *nom);
dossier *creer_dossier(const char *name, dossier *parent);
dossier *chercher_sous_dossier(dossier *parent, const char *nom);
void suprimer_dossier(dossier *parent, const char *nom);
dossier *creer_dossier(const char *name, dossier *parent);
void afficher_arborescence(dossier *d, int profondeur);
void afficher_dossier(dossier *d);

/* Fichiers */
Fichier *creer_fichier(char *name, dossier *parent);
Fichier *chercher_sous_fichier(dossier *parent, const char *nom);
int indice_fichier(dossier *parent, const char *nom);
void read_fichier(Fichier *f);
void write_fichier(Fichier *f, char *text);
void append_fichier(Fichier *f, char *text);
void suprimer_fichier(dossier *parent, const char *nom);

/* Systeme de fichiers et deplacements */
Filesystem *init_Filesystem(void);
int longueur_premier_element(const char *chemin);
Filesystem *déplacement(Filesystem *fs, char *destination);

/* Espace memoire */
size_t espace_utilise_dossier(dossier *d);
size_t espace_utilise(Filesystem *fs);
size_t espace_disponible(Filesystem *fs);


#endif
