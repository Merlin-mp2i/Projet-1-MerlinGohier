#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 50
#define ESPACE_TOTAL 10000

/* Un dossier peut contenir d'autres dossiers et des fichiers. */
typedef struct dossier dossier;

typedef struct Fichier {
    char *name;          /* Nom du fichier. */
    char *content;       /* Texte contenu dans le fichier. */
    size_t taille;       /* Nombre de caracteres du contenu. */
    dossier *parent;     /* Dossier qui contient ce fichier. */
} Fichier;

struct dossier {
    char *name;          /* Nom du dossier. */
    dossier *parent;     /* NULL pour la racine. */
    Fichier **files;     /* Tableau de pointeurs vers les fichiers. */
    int fn;              /* Nombre de fichiers. */
    dossier **next;      /* Tableau de pointeurs vers les sous-dossiers. */
    int fd;              /* Nombre de sous-dossiers. */
};

typedef struct {
    dossier *root;
    dossier *current;
    size_t espace_total; /* Capacite maximale du systeme. */
} Filesystem;

/* Dossiers */
bool est_vide_dossier_d(const dossier *p);
bool est_vide_dossier_f(const dossier *p);
int indice_dossier(const dossier *parent, const char *nom);
dossier *creer_dossier(const char *name, dossier *parent);
dossier *chercher_sous_dossier(dossier *parent, const char *nom);
void suprimer_dossier(dossier *parent, const char *nom);
void afficher_arborescence(const dossier *d, int profondeur);
void afficher_dossier(const dossier *d);

/* Fichiers */
Fichier *creer_fichier(const char *name, dossier *parent);
Fichier *chercher_sous_fichier(dossier *parent, const char *nom);
int indice_fichier(const dossier *parent, const char *nom);
void read_fichier(const Fichier *f);
void write_fichier(Fichier *f, const char *text);
void append_fichier(Fichier *f, const char *text);
void suprimer_fichier(dossier *parent, const char *nom);

/* Systeme de fichiers et deplacements */
Filesystem *init_Filesystem(void);
void detruire_filesystem(Filesystem *fs);
int longueur_premier_element(const char *chemin);
Filesystem *deplacement(Filesystem *fs, const char *destination);

/* Espace memoire */
size_t espace_utilise_dossier(const dossier *d);
size_t espace_utilise(const Filesystem *fs);
size_t espace_disponible(const Filesystem *fs);

#endif
