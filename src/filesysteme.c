#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define max 50

/* STRUCTURE PRIMAIRE  */
typedef struct Fichier{
    char *name;
    char *content;
    struct Fichier *next;
} Fichier;

typedef struct dossier
{
    char *name;
    struct dossier *parent;
    Fichier *files;
    int fn; 
    struct dossier *next;
    int fd;
} dossier;

typedef struct 
{
    dossier *root;
    dossier *current;
} Filesystem;

/* METHODE */

bool est_vide_dossier_d(dossier *p){
    return p->fd == 0;
}

bool est_vide_dossier_f(dossier *p){
    return p->fn == 0;
}

dossier *creer_dossier(const char *name, dossier *parent){
    dossier *d = malloc(sizeof(dossier));
    if (d == NULL) {
        return NULL;
    }

    d->name = malloc(strlen(name) + 1);
    if (d->name == NULL) {
        free(d);
        return NULL;
    }
    strcpy(d->name, name);

    d->fn = 0;
    d->fd = 0;
    d->files = NULL;
    d->next = NULL;
    d->parent = parent;

    if (parent != NULL){
        if(est_vide_dossier_d(parent)){
            parent->fd += 1;
            parent->next = malloc(sizeof(dossier));
        }
        else{
            parent->fd += 1;
            parent->next = realloc(parent->next, parent->fd * sizeof(dossier));

        }
        parent->next[parent->fd-1] = *d;
    }

    return d;
}

Filesystem *init_Filesystem (){
    Filesystem *fs = malloc(sizeof(Filesystem));
    if (fs == NULL) {
        return NULL;
    }
    fs->root = creer_dossier("root",NULL);
    fs->current = fs->root;
    return fs;
}
