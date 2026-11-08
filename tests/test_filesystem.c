#include "../include/filesytem.h"

#include <assert.h>

/* Libere une arborescence creee pour un test. */
static void liberer_dossier(dossier *d) {
    while (d != NULL && d->fn > 0) {
        suprimer_fichier(d, d->files[0]->name);
    }
    while (d != NULL && d->fd > 0) {
        suprimer_dossier(d, d->next[0]->name);
    }
    if (d != NULL) {
        free(d->name);
        free(d);
    }
}

static void liberer_filesystem(Filesystem *fs) {
    if (fs != NULL) {
        liberer_dossier(fs->root);
        free(fs);
    }
}

static void test_creation_dossiers_et_fichiers(void) {
    Filesystem *fs = init_Filesystem();
    dossier *cours;
    Fichier *note;

    assert(fs != NULL);
    assert(strcmp(fs->root->name, "root") == 0);
    assert(est_vide_dossier_d(fs->root));
    assert(est_vide_dossier_f(fs->root));

    cours = creer_dossier("cours", fs->root);
    note = creer_fichier("note", cours);

    assert(cours != NULL);
    assert(note != NULL);
    assert(fs->root->fd == 1);
    assert(cours->fn == 1);
    assert(chercher_sous_dossier(fs->root, "cours") == cours);
    assert(chercher_sous_fichier(cours, "note") == note);
    assert(indice_dossier(fs->root, "cours") == 0);
    assert(indice_fichier(cours, "note") == 0);

    liberer_filesystem(fs);
}

static void test_ecriture_ajout_et_espace(void) {
    Filesystem *fs = init_Filesystem();
    Fichier *fichier = creer_fichier("journal", fs->root);

    assert(fichier != NULL);
    write_fichier(fichier, "Bonjour");
    assert(strcmp(fichier->content, "Bonjour") == 0);
    assert(fichier->taille == 7);
    assert(espace_utilise(fs) == 7);

    append_fichier(fichier, " MP2I");
    assert(strcmp(fichier->content, "Bonjour MP2I") == 0);
    assert(fichier->taille == 12);
    assert(espace_utilise(fs) == 12);
    assert(espace_disponible(fs) == ESPACE_TOTAL - 12);

    write_fichier(fichier, "ok");
    assert(fichier->taille == 2);
    assert(espace_utilise(fs) == 2);

    liberer_filesystem(fs);
}

static void test_deplacements(void) {
    Filesystem *fs = init_Filesystem();
    dossier *cours = creer_dossier("cours", fs->root);
    dossier *c = creer_dossier("c", cours);

    assert(déplacement(fs, "cours") == fs);
    assert(fs->current == cours);
    assert(déplacement(fs, "c") == fs);
    assert(fs->current == c);
    assert(déplacement(fs, "..") == fs);
    assert(fs->current == cours);
    assert(déplacement(fs, "/cours/c") == fs);
    assert(fs->current == c);
    assert(déplacement(fs, "inexistant") == NULL);
    assert(fs->current == c);

    liberer_filesystem(fs);
}

static void test_suppressions_recursives(void) {
    Filesystem *fs = init_Filesystem();
    dossier *cours = creer_dossier("cours", fs->root);
    dossier *chapitre = creer_dossier("chapitre", cours);
    Fichier *note = creer_fichier("note", chapitre);

    write_fichier(note, "contenu");
    assert(espace_utilise(fs) == 7);

    suprimer_dossier(fs->root, "cours");
    assert(fs->root->fd == 0);
    assert(chercher_sous_dossier(fs->root, "cours") == NULL);
    assert(espace_utilise(fs) == 0);

    liberer_filesystem(fs);
}

int main(void) {
    test_creation_dossiers_et_fichiers();
    test_ecriture_ajout_et_espace();
    test_deplacements();
    test_suppressions_recursives();

    printf("Tous les tests unitaires sont passes.\n");
    return 0;
}
