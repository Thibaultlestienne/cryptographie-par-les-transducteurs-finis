#include "francais.h"

double indiceCoincidenceFrancaisSimple(double freqSimple[26]){
    double retour = 0;
    for(int i = 0; i<26; i++){
        retour -= valeurAbsolue(freqSimple[i] - FREQUENCETHEORIQUE[i]);
    }
    return retour;
}

double indiceCoincidenceFrancaisCouple(double freqDouble[26][26]){
    double retour = 0;
    for(int i = 0; i<26; i++){
        for(int j = 0; j<26; j++){
            retour -= valeurAbsolue(freqDouble[i][j] - FREQUENCECOUPLETHEORIQUE[i][j]);
        }
    }
    return retour;
}

double indiceCoincidenceFrancaisGlobal(double freqSimple[26], double freqDouble[26][26]){
    return 10 * indiceCoincidenceFrancaisSimple(freqSimple) + indiceCoincidenceFrancaisCouple(freqDouble);
}

double indiceCoincidenceFrancaisGlobalV2(double freqSimple[26], double freqDouble[26][26]){
    double retour = 0;
    for  (int i = 0; i < 26; i++){
        for (int j = 0; j < 26; j++){
            if (FREQUENCECOUPLETHEORIQUE[i][j] ==  0){
                continue;
                //retour -= freqDouble[i][j] * 10000;
            }
            else {
                retour +=  freqDouble[i][j] * log(FREQUENCECOUPLETHEORIQUE[i][j]);
        
            }
        }
    }
    return retour ;
}

// int main(){
//     initialiserAleatoire();
//     char texte[TAILLE_MESSAGE];
//     texteAleatoireFrancais(texte, TAILLE_MESSAGE);
//     char textealeatoire[TAILLE_MESSAGE];
//     texteAleatoire(textealeatoire, TAILLE_MESSAGE);
//     double freqSimple[26];
//     double freqDouble[26][26];
//     freqSimpleTexte(texte, freqSimple);
//     freqCoupleTexte(texte, freqDouble);
//     printf("Indice simple : %f\n", indiceCoincidenceFrancaisSimple(freqSimple));
//     printf("Indice double : %f\n", indiceCoincidenceFrancaisCouple(freqDouble));
//     freqSimpleTexte(textealeatoire, freqSimple);
//     freqCoupleTexte(textealeatoire, freqDouble);
//     printf("Indice simple aleatoire : %f\n", indiceCoincidenceFrancaisSimple(freqSimple));
//     printf("Indice double aleatoire : %f\n", indiceCoincidenceFrancaisCouple(freqDouble));
//     return 0;
// }