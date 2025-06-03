#include "maths.h"

double valeurAbsolue(double n) {
    if (n < 0) {return (-n);}
    else {return n;}
}

// assert(valeurAbsolue (0) == 0);
// assert(valeurAbsolue (0.5) == 0.5);
// assert(valeurAbsolue (-1.5) == 1.5);
// printf("test ok \n");

int * triIndices(double tab[], int taille) {
    int * indices = malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++) {
        indices[i] = i;
    }
    for (int i = 0; i < taille; i++) {
        for (int j = i + 1; j < taille; j++) {
            if (tab[indices[i]] < tab[indices[j]]) {
                int tmp = indices[i];
                indices[i] = indices[j];
                indices[j] = tmp;
            }
        }
    }
    return indices;
}

void copierTableau(double tableauOriginal[], double tableauCopiee[], int taille) {
    for (int i = 0; i < taille; i++) {
        tableauCopiee[i] = tableauOriginal[i];
    }
}

void copierMatriceCarree(double **matriceOriginale, double **matriceCopiee, int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            matriceCopiee[i][j] = matriceOriginale[i][j];
        }
    }
} 