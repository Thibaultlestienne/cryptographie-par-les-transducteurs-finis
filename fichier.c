#include "fichier.h"

void enregistrerTransducteur(transducteur trans, char* nomFichier){
    
    char nom_complet[200] ;
    sprintf(nom_complet, "%s/%s.%s",DOSSIERTRANSDUCTEUR, nomFichier, EXTENTIONTRANSDUCTEUR);
    
    // ouverture du fichier
    FILE *fichier = fopen(nom_complet, "w");
    if (fichier == NULL) {
        printf("\n !!! Erreur d'ouverture du fichier %s (ecriture) !!! \n", nomFichier);
        exit(EXIT_FAILURE);
    }

    // nbEtat et nbLettre
    fprintf(fichier, "nb Etat : %d, nb Lettre : %d\n", trans.nbEtat, trans.nbLettre);

    fprintf(fichier, "Delta : \n");

    // delta
    for (int i = 0; i < trans.nbEtat; i++) {
        for (int j = 0; j < trans.nbLettre; j++) {
            fprintf(fichier, "|%d %c\t", trans.delta[i][j].etat, trans.delta[i][j].lettre);
        }
        fprintf(fichier, "|\n");
    }

    fclose(fichier);
}


transducteur* chargerTransducteur(const char *nomFichier) {
    char nom_complet[200] ;
    sprintf(nom_complet, "%s/%s.%s",DOSSIERTRANSDUCTEUR, nomFichier, EXTENTIONTRANSDUCTEUR);

    // Ouverture du fichier
    FILE *fichier = fopen(nom_complet, "r");
    if (fichier == NULL) {
        printf("\n !!! Erreur d'ouverture du fichier %s (lecture) !!! \n", nomFichier);
        exit(EXIT_FAILURE);
    }

    // nbEtat et nbLettre
    int nombreEtat, nombreLettre;
    assert(fscanf(fichier, "nb Etat : %d, nb Lettre : %d\n", &nombreEtat, &nombreLettre) == 2);

    // Initialisation du transducteur
    transducteur* trans = initialiserTransducteur(nombreEtat, nombreLettre);

    // Lecture de la matrice delta
    char buffer[1000]; // Pour sauter les lignes inutiles
    fgets(buffer, sizeof(buffer), fichier); // Sauter la ligne "Delta :"
    for (int i = 0; i < trans->nbEtat; i++) {
        for (int j = 0; j < trans->nbLettre; j++) {
            if (fscanf(fichier, "|%d %c\t", &trans->delta[i][j].etat, &trans->delta[i][j].lettre) != 2) {
                printf("Erreur de lecture des transitions");
                for (int k = 0; k <= i; k++) {
                    free(trans->delta[k]);
                }
                free(trans->delta);
                free(trans);
                fclose(fichier);
                exit(EXIT_FAILURE);
            }
        }
        fgets(buffer, sizeof(buffer), fichier); // Sauter jusqu'à la fin de la ligne
    }

    fclose(fichier);
    return trans;

}

// int main(){
//     char clair[TAILLE_MAX_TEXTE] = "ababbababbbbbababbbbbaaaaababa";
//     char encode1[TAILLE_MAX_TEXTE];
//     transducteur * trans1 = exemple1();
//     codeTransducteur(clair, encode1, *trans1);

//     char encode2[TAILLE_MAX_TEXTE];
//     enregistrerTransducteur(*trans1,"ex1");
//     transducteur * trans2 = chargerTransducteur("ex1");
//     codeTransducteur(clair, encode2, *trans2);

//     assert(strcmp(encode1,encode2) == 0);
    
//     libererTransducteur(trans1);
//     libererTransducteur(trans2);

//     printf("TEST OK \n");
//     return 0;
// }