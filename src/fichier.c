#include "../include/filesytem.h"

/* Cree un fichier vide puis l'ajoute au dossier parent. */
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
    f->taille = 0;
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

/* Remplace entierement le contenu d'un fichier. */
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
    f->taille = strlen(text);
}

/* Agrandit le contenu du fichier puis ajoute le nouveau texte a la fin. */
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
    f->taille = strlen(f->content);
}

int indice_fichier(dossier *parent, const char *nom){
    for(int i = 0; i< parent->fn; i++ ){
        if(strcmp(nom, parent->files[i]->name) == 0){
            return i;
        }
    }
    return -1;
}

/* Libere le fichier puis decale les fichiers suivants dans le tableau. */
void suprimer_fichier (dossier *parent, const char *nom){
    int indice;
    int i;
    Fichier **nouveaux_fichiers;

    if (parent == NULL || nom == NULL) {
        return;
    }

    indice = indice_fichier(parent, nom);
    if (indice == -1) {
        return;
    }

    free(parent->files[indice]->content);
    free(parent->files[indice]->name);
    free(parent->files[indice]);

    for (i = indice; i < parent->fn - 1; i++) {
        parent->files[i] = parent->files[i + 1];
    }

    parent->fn -= 1;

    if (parent->fn == 0) {
        free(parent->files);
        parent->files = NULL;
    } else {
        nouveaux_fichiers = realloc(parent->files, parent->fn * sizeof(Fichier *));
        if (nouveaux_fichiers != NULL) {
            parent->files = nouveaux_fichiers;
        }
    }
}
