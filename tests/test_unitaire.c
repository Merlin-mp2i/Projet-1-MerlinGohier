#include <assert.h>
#include <stdio.h>
#include "../include/filesytem.h"

/*
 * Test volontairement court : il couvre creation, ecriture, ajout,
 * navigation, suppression et calcul de l'espace utilise.
 */
int main(void) {
    Filesystem *fs = init_Filesystem();
    dossier *cours;
    Fichier *note;

    assert(fs != NULL);
    assert(espace_utilise(fs) == 0);

    cours = creer_dossier("cours", fs->root);
    assert(cours != NULL);
    assert(creer_dossier("cours", fs->root) == NULL); /* nom deja pris */

    note = creer_fichier("note", cours);
    assert(note != NULL);
    assert(creer_fichier("note", cours) == NULL); /* nom deja pris */

    write_fichier(note, "bonjour");
    append_fichier(note, " MP2I");
    assert(strcmp(note->content, "bonjour MP2I") == 0);
    assert(espace_utilise(fs) == 12);

    assert(deplacement(fs, "cours") == fs);
    assert(fs->current == cours);
    assert(deplacement(fs, "..") == fs);
    assert(fs->current == fs->root);

    suprimer_dossier(fs->root, "cours");
    assert(indice_dossier(fs->root, "cours") == -1);
    assert(espace_utilise(fs) == 0);

    detruire_filesystem(fs);
    puts("Tests unitaires : OK");
    return 0;
}
