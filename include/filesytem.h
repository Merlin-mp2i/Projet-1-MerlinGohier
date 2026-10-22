#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define max 50
/* =======================
   STRUCTURES
   ======================= */

typedef struct dossier dossier;

typedef struct Fichier{
    char *name;
    char *content;
    dossier *parent;
} Fichier;

struct dossier
{
    char *name;
    dossier *parent;
    Fichier **files;
    int fn;
    dossier **next;
    int fd;
};

typedef struct
{
    dossier *root;
    dossier *current;
} Filesystem;


/* =======================
   PROTOTYPES
   ======================= */

bool est_vide_dossier_d(dossier *p);
bool est_vide_dossier_f(dossier *p);

int indice_dossier(dossier *parent, const char *nom);

void suprimer_dossier(dossier *parent, const char *nom);

dossier *creer_dossier(const char *name, dossier *parent);

Filesystem *init_Filesystem(void);

int longueur_premier_element(const char *chemin);

dossier *chercher_sous_dossier(dossier *parent, const char *nom);

Filesystem *déplacement(Filesystem *fs, char *destination);

Fichier *creer_fichier(char *name, dossier *parent);

void read_fichier(Fichier *f);

void write_fichier(Fichier *f, char *text);

void append_fichier(Fichier *f, char *text);

int indice_fichier(dossier *parent, const char *nom);

void suprimer_fichier(dossier *parent, const char *nom);

void afficher_arborescence (dossier*d, int profondeur);

void afficher_dossier(dossier *d);


#endif
