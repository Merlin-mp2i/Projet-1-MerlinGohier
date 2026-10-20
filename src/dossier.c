#include "../include/filesytem.h"

/* Methode dossier */

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
        parent->next[parent->fd-1] = d;
    }

    return d;
}

void afficher_dossier (dossier*d, int profondeur){
    for (int i = 0; i < profondeur; i++) {
        printf(" ");
    }
    printf("%s \n",d->name);
    if(!est_vide_dossier_f(d)){
        for(int i = 0; i < d->fn; i++){
            for (int j = 0; j < profondeur + 1; j++) {
                printf(" ");
            }
            printf("|__%s \n", d->files[i]->name);
        }
    }
    if(!est_vide_dossier_d(d)){
        for(int i = 0; i < d->fd; i++){
            afficher_dossier(d->next[i],profondeur+1 );
        }
    }
}
