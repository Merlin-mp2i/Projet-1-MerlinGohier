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

void read_fichier (Fichier *f){
    if (f != NULL && f->content != NULL) {
        printf("%s", f->content);
    }
}

void write_fichier (Fichier *f, char *text){
    char *nouveau_contenu;

    if (f == NULL || text == NULL) {
        return;
    }

    nouveau_contenu = malloc(strlen(text) + 1);
    if (nouveau_contenu == NULL) {
        return;
    }

    strcpy(nouveau_contenu, text);
    free(f->content);
    f->content = nouveau_contenu;
}

void append_fichier(Fichier *f, char *text){
    char *nouveau_contenu;
    int taille_ancien;
    int taille_ajout;
    int i;

    if (f == NULL || text == NULL) {
        return;
    }

    if (f->content == NULL) {
        taille_ancien = 0;
    } else {
        taille_ancien = strlen(f->content);
    }

    taille_ajout = strlen(text);
    nouveau_contenu = realloc(f->content, taille_ancien + taille_ajout + 1);
    if (nouveau_contenu == NULL) {
        return;
    }

    for (i = 0; i <= taille_ajout; i++) {
        nouveau_contenu[taille_ancien + i] = text[i];
    }

    f->content = nouveau_contenu;
}
