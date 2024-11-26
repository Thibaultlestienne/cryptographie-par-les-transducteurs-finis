#include "transducteur.h"

transducteur* initialiserTransducteur(int nombreEtat, int nombreLettre){ // alloue la memoire pour le transducteur
    transducteur* trans = malloc(sizeof(transducteur));
    assert(trans != NULL);
    trans->nbEtat = nombreEtat;
    trans->nbLettre = nombreLettre;
    trans->delta = malloc(sizeof(transition*) * nombreEtat);
    assert(trans->delta != NULL);
    for (int i = 0 ; i < nombreEtat; i++){
        trans->delta[i]=malloc(sizeof(transition) * nombreLettre);
        assert(trans->delta[i] != NULL);
    }
    return trans;
}

void libererTransducteur(transducteur* trans){
    for (int i = 0 ; i < trans->nbEtat; i++){
        free(trans->delta[i]);
    }
    free(trans->delta);
    free(trans);
}
// TEST !!! Utiliser fsanitize !!! 
// transducteur * trans =initialiserTransducteur(4,5);
// libererTransducteur(trans);

transducteur* exemple1(){ // Transducteur exemple 
    transducteur* ex = initialiserTransducteur(2,2);
    // Etat 0
        // depuis l'état 0 un a 
        ex->delta[0][0].etat = 1;
        ex->delta[0][0].lettre = 'b';
        // depuis l'état 0 un b
        ex->delta[0][1].etat = 1;
        ex->delta[0][1].lettre = 'a';

    // Etat 1
        // depuis l'état 0 un a 
        ex->delta[1][0].etat = 0;
        ex->delta[1][0].lettre = 'a';
        // depuis l'état 0 un b
        ex->delta[1][1].etat = 1;
        ex->delta[1][1].lettre = 'b';

    return ex;
}

void codeTransducteur(char * messageClair, char * messageEncode, transducteur trans ){
    int etatActif = 0;
    enleverAccentsEspacePonctuationMajuscule(messageClair);

    int i = 0;
    for(;messageClair[i] != '\0'; i++){
        messageEncode[i] = trans.delta[etatActif][messageClair[i] - 'a'].lettre;
        etatActif = trans.delta[etatActif][messageClair[i] - 'a'].etat;
    }
    messageEncode[i] = '\0';
}

// inserser le transducteru avant de decoder

// TEST
// char clair[TAILLE_MAX_TEXTE] = "aaabbaba";
// char encode[TAILLE_MAX_TEXTE] ;
// transducteur* trans = exemple1();
// codeTransducteur(clair, encode, *trans);
// // printf("exemple 1 encode %s en %s \n",clair, encode);
// assert(strcmp(encode, "babbbaaa") == 0);
// libererTransducteur(trans);
// printf("TEST OK \n");


int main(){

}