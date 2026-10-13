#include <stdio.h>
#include <stdlib.h>
#define max 50


/* STRUCTURE PRIMAIRE  */
typedef struct{
    char *name;
    char *content;
    struct Fichier *next;
} Fichier;

typedef struct
{
    char *name;
    struct dossier *parent;
    Fichier *files;
    struct dossier *subdirs;
    struct dossier *next;
}dossier;

typedef struct 
{
    dossier *root;
    dossier *current;
}Filesystem;

/* METHODE */

Filesystem *init_Filesystem (){
    Filesystem *fs = malloc(sizeof(Filesystem));
    if (fs == NULL) {
        return NULL;
    }
    fs->root = creer_dossier("root");
    fs->current = fs->root;
    return fs;
}
