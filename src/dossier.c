#include "../include/filesytem.h"

bool est_vide_dossier_d(dossier *p){
    return p->fd == 0;
}

bool est_vide_dossier_f(dossier *p){
    return p->fn == 0;
}


/* Cree un dossier vide et l'ajoute au dossier parent. */
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

/* Affiche le dossier, ses fichiers, puis ses sous-dossiers. */
void afficher_arborescence (dossier*d, int profondeur){
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
            afficher_arborescence(d->next[i],profondeur+1 );
        }
    }
}

void afficher_dossier (dossier*d){
    for(int i = 0; i < d->fn; i++){
        printf("|__%s \n", d->files[i]->name);
        }
        for(int i = 0; i < d->fd; i++){
            printf("|__%s \n", d->next[i]->name);
        }
}

int indice_dossier(dossier *parent, const char *nom){
    for(int i = 0; i< parent->fd; i++ ){
        if(strcmp(nom, parent->next[i]->name) == 0){
            return i;
        }
    }
    return -1;
}

/* Vide recursivement le dossier avant de le retirer de son parent. */
void suprimer_dossier(dossier *parent, const char *nom){
    int indice;
    int i;
    dossier **nouveaux_dossier;
    dossier *a_supprimer;

    if (parent == NULL || nom == NULL) {
        return;
    }

    indice = indice_dossier(parent, nom);
    if (indice == -1) {
        return;
    }

    a_supprimer = parent->next[indice];

    /* On vide tous les fichiers du dossier. */
    while (a_supprimer->fn > 0) {
        suprimer_fichier(a_supprimer, a_supprimer->files[0]->name);
    }

    /* On vide tous les sous-dossiers, y compris leur contenu. */
    while (a_supprimer->fd > 0) {
        suprimer_dossier(a_supprimer, a_supprimer->next[0]->name);
    }

    free(a_supprimer->name);
    free(a_supprimer);

    for (i = indice; i < parent->fd - 1; i++) {
        parent->next[i] = parent->next[i + 1];
    }
    parent->fd -= 1;

    if (parent->fd == 0) {
        free(parent->next);
        parent->next = NULL;
    } else {
        nouveaux_dossier = realloc(parent->next, parent->fd * sizeof(dossier *));
        if (nouveaux_dossier != NULL) {
            parent->next = nouveaux_dossier;
        }
    }
}
