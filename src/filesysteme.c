#include "../include/filesytem.h"

/* Cree la racine et place l'utilisateur dans cette racine. */
Filesystem *init_Filesystem (){
    Filesystem *fs = malloc(sizeof(Filesystem));
    if (fs == NULL) {
        return NULL;
    }
    fs->root = creer_dossier("root",NULL);
    if (fs->root == NULL) {
        free(fs);
        return NULL;
    }
    fs->current = fs->root;
    fs->espace_total = ESPACE_TOTAL;
    return fs;
}

/* Additionne la taille des fichiers du dossier et de ses enfants. */
size_t espace_utilise_dossier(dossier *d) {
    size_t total = 0;
    int i;

    if (d == NULL) {
        return 0;
    }

    for (i = 0; i < d->fn; i++) {
        total += d->files[i]->taille;
    }

    for (i = 0; i < d->fd; i++) {
        total += espace_utilise_dossier(d->next[i]);
    }

    return total;
}

size_t espace_utilise(Filesystem *fs) {
    if (fs == NULL) {
        return 0;
    }

    return espace_utilise_dossier(fs->root);
}

/* Calcule ce qu'il reste dans la capacite choisie. */
size_t espace_disponible(Filesystem *fs) {
    size_t utilise = espace_utilise(fs);

    if (fs == NULL || utilise >= fs->espace_total) {
        return 0;
    }

    return fs->espace_total - utilise;
}

/* Compte les caracteres avant le prochain slash. */
int longueur_premier_element(const char *chemin) {
    int i = 0;

    while (chemin[i] != '\0' && chemin[i] != '/') {
        i++;
    }

    return i;
}
Fichier *chercher_sous_fichier(dossier *parent, const char *nom) {
    for (int i = 0; i < parent->fn; i++) {
        if (strcmp(nom, parent->files[i]->name) == 0) {
            return parent->files[i];
        }
    }

    return NULL;
}

dossier *chercher_sous_dossier(dossier *parent, const char *nom) {
    for (int i = 0; i < parent->fd; i++) {
        if (strcmp(nom, parent->next[i]->name) == 0) {
            return parent->next[i];
        }
    }

    return NULL;
}

/* Lit le chemin mot par mot et change le dossier courant. */
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
