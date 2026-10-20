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
