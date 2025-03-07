#include "resultats.h"

// int main(){
//     initialiserAleatoire();
//     transducteur * t = TransducteurUniforme(1000,26);
//     char claire[TAILLE_MAX_TEXTE];
//     char code[TAILLE_MAX_TEXTE];
//     char decode[TAILLE_MAX_TEXTE];
//     texteAleatoireFrancais(claire, TAILLE_MAX_TEXTE-1);
//     codeTransducteur(claire, code, *t);
//     decodeTransducteur(code, decode, t);

//     // printf("claire : %s\n", claire);
//     // printf("  code : %s\n", code);
//     // printf("decode : %s\n", decode);

//     assert(strcmp(decode,claire) == 0);
//     double tabfreq[26] = {0};
//     freqSimpleTexte(code, tabfreq);
//     for (int i = 0; i < 26; i ++) {
//         printf("Fréquence de %c : %lf\n", i + 'a', tabfreq[i]);
//     }

//     // frequence des couples
//     double tabfreq2[26][26] = {0};
//     freqCoupleTexte(code, tabfreq2);
//     for (int i = 0; i < 26; i ++) {
//         for (int j = 0; j < 26; j ++) {
//             printf("Fréquence de %c%c : %lf\n", i + 'a', j + 'a', tabfreq2[i][j]);
//         }
//     }
// }

int main(){
    if (FREQUENCESIMPLEFRANCAIS) {
        double tabsimple[26];
        freqSimpleFichier(FICHIERPOURANALYSE, tabsimple);
        for (int i = 0; i < 26; i ++) {
            printf("Fréquence de %c : %.15lf\n", i + 'a', tabsimple[i]);
        }
    }
    if (FREQUENCECOUPLEFRANCAIS) {
        double tabcouple[26][26];
        freqCoupleFichier(FICHIERPOURANALYSE, tabcouple);
        for (int i = 0; i < 26; i ++) {
            for (int j = 0; j < 26; j ++) {
                printf("Fréquence de %c%c : %.15lf\n", i + 'a', j + 'a', tabcouple[i][j]);
            }
        }
    }
    if (FREQUENCEDOUBLEFRANCAIS) {
        double probalettredouble = 0;
        double tabdouble[26][26];
        freqCoupleFichier(FICHIERPOURANALYSE, tabdouble);
        for (int i = 0; i < 26; i ++) {
            probalettredouble += tabdouble[i][i];
        }
        printf("Probabilité que deux lettres successives soient identiques : %lf\n", probalettredouble);
        // pour le test sur un long texte encode par un transducteur
        initialiserAleatoire();
        transducteur * t = TransducteurUniforme(1000,26);
        codeFichierTransducteur(HUGO, "sortie.txt", *t);
        freqCoupleFichier("sortie.txt", tabdouble);
        double tauxlettredouble = 0;
        for (int i = 0; i < 26; i ++) {
            tauxlettredouble += tabdouble[i][i];
        }
        printf("Probabilité que deux lettres successives soient identiques sur un texte encode par un transducteur : %.10lf\n", tauxlettredouble);
        printf("Nombre de sommet prevu : %d théorique %lf \n", t->nbEtat, (26*probalettredouble-1)/(26*tauxlettredouble-1));
    }

    if (DECODERCESAR) {
        initialiserAleatoire();
        int compteur = 0;

        for (int i = 0; i < NOMBRETESTCESAR; i++) {
            char claire[TAILLE_MAX_TEXTE];
            char code[TAILLE_MAX_TEXTE];
            char decode[TAILLE_MAX_TEXTE];
            texteAleatoireFrancais(claire, TAILLEMESSAGECESAR);
            int cle = entierAleatoire(0,25);
            codeCesar(claire, code, cle);
            if (decodeCesarTexte(code, decode) == cle) {
                compteur ++;
            }
            if (AFFICHAGECESAR) {printf("Cesar cas %d\n\tclaire : %s \n\tcode   : %s \n\tdecode : %s \n", i, claire, code, decode);}
        }
        printf("Taux de réussite Cesar sans clé : %lf\n", compteur/(double)NOMBRETESTCESAR);
    }

    if (DECODERVIGENERE) {
        initialiserAleatoire();
        int compteur = 0;

        for (int i = 0; i < NOMBRETESTVIGENERE; i++) {
            char claire[TAILLE_MAX_TEXTE];
            char code[TAILLE_MAX_TEXTE];
            char decode[TAILLE_MAX_TEXTE];
            texteAleatoireFrancais(claire, TAILLEMESSAGEVIGENERE);
            char cle[TAILLE_MAX_TEXTE];
            texteAleatoire(cle, TAILLECLEVIGENERE);
            codeVigenere(claire, code, cle);
            char cleTrouvee[TAILLE_MAX_TEXTE];
            decodeVigenereSansCle(code, decode, 0.065, cleTrouvee);
            if (strcmp(cle, cleTrouvee) == 0) {
                compteur ++;
            }
            if (AFFICHAGEVIGENERE) {printf("Vigenere cas %i \n\tclé reel     : %s \n\tcle detectee : %s \n\tclaire : %s \n\tcode   : %s \n\tdecode : %s \n", i, cle, cleTrouvee, claire, code, decode);}
        }
        printf("Taux de réussite Vigenere sans clé : %lf\n", compteur/(double)NOMBRETESTVIGENERE);
    }
}