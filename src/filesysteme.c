#include "../include/filesytem.h"

/* Methode Filesystem */

Filesystem *init_Filesystem (){
    Filesystem *fs = malloc(sizeof(Filesystem));
    if (fs == NULL) {
        return NULL;
    }
    fs->root = creer_dossier("root",NULL);
    fs->current = fs->root;
    return fs;
}

int longueur_premier_element(const char *chemin) {
    int i = 0;

    while (chemin[i] != '\0' && chemin[i] != '/') {
        i++;
    }

    return i;
}

dossier *chercher_sous_dossier(dossier *parent, const char *nom) {
    for (int i = 0; i < parent->fd; i++) {
        if (strcmp(nom, parent->next[i]->name) == 0) {
            return parent->next[i];
        }
    }

    return NULL;
}

Filesystem *déplacement(Filesystem *fs, char *destination) {
    dossier *position;
    char mot[max];
    int index = 0;
    int taille;
    int i;

    if (fs == NULL || destination == NULL) {
        return NULL;
    }

    if (destination[0] == '/') {
        position = fs->root;
    } else {
        position = fs->current;
    }

    while (destination[index] != '\0') {
        if (destination[index] == '/') {
            index++;
        } else {
            taille = longueur_premier_element(&destination[index]);
            if (taille >= max) {
                return NULL;
            }

            for (i = 0; i < taille; i++) {
                mot[i] = destination[index + i];
            }
            mot[taille] = '\0';

            if (strcmp(mot, ".") == 0) {
                /* On reste dans le même dossier. */
            } else if (strcmp(mot, "..") == 0) {
                if (position->parent != NULL) {
                    position = position->parent;
                }
            } else {
                position = chercher_sous_dossier(position, mot);
                if (position == NULL) {
                    return NULL;
                }
            }

            index = index + taille;
        }
    }

    fs->current = position;
    return fs;
}
