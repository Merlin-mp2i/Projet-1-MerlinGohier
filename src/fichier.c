#include "../include/filesytem.h"

/* Methode fichier */

Fichier *creer_fichier (char *name, dossier *parent){
    Fichier *f = malloc(sizeof(Fichier));
    if (f == NULL) {
        return NULL;
    }

    f->name = malloc(strlen(name) + 1);
    if (f->name == NULL) {
        free(f);
        return NULL;
    }
    strcpy(f->name, name);


    f->content = NULL;
    f->parent = parent;

    if (parent != NULL){
        if(est_vide_dossier_f(parent)){
            parent->fn += 1;
            parent->files = malloc(sizeof(Fichier));
        }
        else{
            parent->fn += 1;
            parent->files = realloc(parent->files, parent->fn * sizeof(Fichier));

        }
        parent->files[parent->fn-1] = f;
    }

    return f;
}
