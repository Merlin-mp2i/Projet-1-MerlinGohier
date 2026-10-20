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

dossier *creer_dossier(const char *name, dossier *parent);

Filesystem *init_Filesystem(void);

Fichier *creer_fichier(char *name, dossier *parent);

void afficher_dossier(dossier *d, int profondeur);

#endif
