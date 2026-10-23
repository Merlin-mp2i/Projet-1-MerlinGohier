#include "./include/filesytem.h"

int main(void) {
    char ligne[256];       /* Ligne saisie par l'utilisateur. */
    char *commande;        /* Premier mot de la ligne. */
    char *argument;        /* Deuxieme mot : nom, chemin, etc. */
    char *texte;           /* Reste de la ligne pour write et append. */
    Filesystem *user = init_Filesystem();

    if (user == NULL) {
        return 1;
    }

    while (true) {
        /* Le prompt affiche le dossier dans lequel on se trouve. */
        printf("%s > ", user->current->name);

        /* fgets lit toute la ligne, espaces compris. */
        if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
            break;
        }

        /* Le premier mot est toujours le nom de la commande. */
        commande = strtok(ligne, " \r\n");
        if (commande == NULL) {
            continue;
        }

        /* exit arrete la boucle principale. */
        if (strcmp(commande, "exit") == 0) {
            break;
        }

        /* On recupere le nom ou le chemin place apres la commande. */
        argument = strtok(NULL, " \r\n");

        if (strcmp(commande, "ls") == 0) {
            afficher_dossier(user->current);

        } else if (strcmp(commande, "mkdir") == 0 && argument != NULL) {
            creer_dossier(argument, user->current);

        } else if (strcmp(commande, "touch") == 0 && argument != NULL) {
            creer_fichier(argument, user->current);

        } else if (strcmp(commande, "cd") == 0 && argument != NULL) {
            if (déplacement(user, argument) == NULL) {
                printf("Dossier introuvable.\n");
            }

        } else if (strcmp(commande, "read") == 0 && argument != NULL) {
            int indice = indice_fichier(user->current, argument);

            if (indice == -1) {
                printf("Fichier introuvable.\n");
            } else {
                read_fichier(user->current->files[indice]);
                printf("\n");
            }

        } else if (strcmp(commande, "write") == 0 && argument != NULL) {
            int indice = indice_fichier(user->current, argument);
            Fichier *fichier;

            /* On garde tous les espaces du texte a ecrire. */
            texte = strtok(NULL, "\r\n");
            while (texte != NULL && texte[0] == ' ') {
                texte++;
            }

            if (indice == -1 || texte == NULL) {
                printf("Utilisation : write nom texte\n");
            } else {
                fichier = user->current->files[indice];
                /* write remplace le texte : on retire donc son ancienne taille. */
                if (espace_utilise(user) - fichier->taille + strlen(texte) > user->espace_total) {
                    printf("Espace insuffisant.\n");
                } else {
                    write_fichier(fichier, texte);
                }
            }

        } else if (strcmp(commande, "append") == 0 && argument != NULL) {
            int indice = indice_fichier(user->current, argument);
            /* append ajoute tout ce qui reste sur la ligne. */
            texte = strtok(NULL, "\r\n");
            while (texte != NULL && texte[0] == ' ') {
                texte++;
            }

            if (indice == -1 || texte == NULL) {
                printf("Utilisation : append nom texte\n");
            } else if (strlen(texte) > espace_disponible(user)) {
                printf("Espace insuffisant.\n");
            } else {
                append_fichier(user->current->files[indice], texte);
            }

        } else if (strcmp(commande, "del") == 0 && argument != NULL) {
            /* On cherche d'abord un fichier, puis un sous-dossier. */
            if (indice_fichier(user->current, argument) != -1) {
                suprimer_fichier(user->current, argument);
            } else if (indice_dossier(user->current, argument) != -1) {
                suprimer_dossier(user->current, argument);
            } else {
                printf("Fichier ou dossier introuvable.\n");
            }

        } else if (strcmp(commande, "arbo") == 0) {
            afficher_arborescence(user->root, 0);

        } else if (strcmp(commande, "space") == 0) {
            /* L'espace utilise est recalcule a partir de toute l'arborescence. */
            printf("Utilise : %zu / %zu caracteres\n", espace_utilise(user), user->espace_total);
            printf("Disponible : %zu caracteres\n", espace_disponible(user));

        } else {
            printf("Commande inconnue ou argument manquant.\n");
        }
    }

    return 0;
}
