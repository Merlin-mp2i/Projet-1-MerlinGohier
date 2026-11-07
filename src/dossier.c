#include "../include/filesytem.h"

bool est_vide_dossier_d(const dossier *p) {
    return p == NULL || p->fd == 0;
}

bool est_vide_dossier_f(const dossier *p) {
    return p == NULL || p->fn == 0;
}

/* Cree un dossier vide et l'ajoute au dossier parent. */
dossier *creer_dossier(const char *name, dossier *parent) {
    dossier *d;
    dossier **nouveaux_dossiers;

    if (name == NULL || name[0] == '\0') {
        return NULL;
    }

    /* Un meme nom ne peut pas designe un fichier et un dossier. */
    if (parent != NULL &&
        (indice_dossier(parent, name) != -1 || indice_fichier(parent, name) != -1)) {
        return NULL;
    }

    d = malloc(sizeof(*d));
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

    if (parent != NULL) {
        nouveaux_dossiers = realloc(parent->next, (size_t)(parent->fd + 1) * sizeof(*parent->next));
        if (nouveaux_dossiers == NULL) {
            free(d->name);
            free(d);
            return NULL;
        }

        parent->next = nouveaux_dossiers;
        parent->next[parent->fd] = d;
        parent->fd += 1;
    }

    return d;
}

/* Affiche le dossier, ses fichiers, puis ses sous-dossiers. */
void afficher_arborescence(const dossier *d, int profondeur) {
    int i;

    if (d == NULL) {
        return;
    }

    for (i = 0; i < profondeur; i++) {
        printf(" ");
    }
    printf("%s\n", d->name);

    for (i = 0; i < d->fn; i++) {
        for (int j = 0; j < profondeur + 1; j++) {
            printf(" ");
        }
        printf("|__%s\n", d->files[i]->name);
    }

    for (i = 0; i < d->fd; i++) {
        afficher_arborescence(d->next[i], profondeur + 1);
    }
}

void afficher_dossier(const dossier *d) {
    int i;

    if (d == NULL) {
        return;
    }

    for (i = 0; i < d->fn; i++) {
        printf("|__%s\n", d->files[i]->name);
    }
    for (i = 0; i < d->fd; i++) {
        printf("|__%s\n", d->next[i]->name);
    }
}

int indice_dossier(const dossier *parent, const char *nom) {
    int i;

    if (parent == NULL || nom == NULL) {
        return -1;
    }

    for (i = 0; i < parent->fd; i++) {
        if (strcmp(nom, parent->next[i]->name) == 0) {
            return i;
        }
    }
    return -1;
}

/* Vide recursivement le dossier avant de le retirer de son parent. */
void suprimer_dossier(dossier *parent, const char *nom) {
    int indice;
    int i;
    dossier *a_supprimer;

    if (parent == NULL || nom == NULL) {
        return;
    }

    indice = indice_dossier(parent, nom);
    if (indice == -1) {
        return;
    }

    a_supprimer = parent->next[indice];

    while (a_supprimer->fn > 0) {
        suprimer_fichier(a_supprimer, a_supprimer->files[0]->name);
    }
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
        /* Si realloc echoue, l'ancien tableau reste valide. */
        dossier **nouveaux_dossiers = realloc(parent->next, (size_t)parent->fd * sizeof(*parent->next));
        if (nouveaux_dossiers != NULL) {
            parent->next = nouveaux_dossiers;
        }
    }
}
