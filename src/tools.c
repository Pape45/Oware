/**
 * Fonctions utilitaires pour la saisie de données
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"


int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');

        if (positionEntree != NULL) {
            *positionEntree = '\0';
        } else {
            viderBuffer();
        }

        return 1;
    } else {
        viderBuffer();
        return 0;     
    }
}

int lireInt() {
    char nombreTexte[100] = {0};
    
    if (lire(nombreTexte, 100)) {
        return atoi(nombreTexte);
    } else {
        return 0;
    }
}

void viderBuffer() {
    int x = 0;
    while (x != '\n' && x != EOF) {
        x = getchar();
    }
}