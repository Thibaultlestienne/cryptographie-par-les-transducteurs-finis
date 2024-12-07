#include "transducteur.h"

transducteur* initialiserTransducteur(int nombreEtat, int nombreLettre){ // alloue la memoire pour le transducteur
    transducteur* trans = malloc(sizeof(transducteur));
    assert(trans != NULL);
    trans->nbEtat = nombreEtat;
    trans->nbLettre = nombreLettre;
    trans->inverse = NULL;
    trans->delta = malloc(sizeof(transition*) * nombreEtat);
    assert(trans->delta != NULL);
    for (int i = 0 ; i < nombreEtat; i++){
        trans->delta[i]=malloc(sizeof(transition) * nombreLettre);
        assert(trans->delta[i] != NULL);
    }
    return trans;
}

void libererTransducteur(transducteur* trans){ 
    if(trans->inverse != NULL){
        for (int i = 0 ; i < trans->inverse->nbEtat; i++){
            free(trans->inverse->delta[i]);
        }
        free(trans->inverse->delta);
        free(trans->inverse);
    }

    for (int i = 0 ; i < trans->nbEtat; i++){
        free(trans->delta[i]);
    }
    free(trans->delta);
    free(trans);
}
// TEST !!! Utiliser fsanitize !!! 
// transducteur * trans = initialiserTransducteur(4,5);
// libererTransducteur(trans);

transducteur* exemple1(){ // Transducteur exemple 
    transducteur* ex = initialiserTransducteur(2,2);
    // Etat 0
        // depuis l'état 0 un a 
        ex->delta[0][0].etat = 1;
        ex->delta[0][0].lettre = 'a';
        // depuis l'état 0 un b
        ex->delta[0][1].etat = 1;
        ex->delta[0][1].lettre = 'b';

    // Etat 1
        // depuis l'état 1 un a 
        ex->delta[1][0].etat = 0;
        ex->delta[1][0].lettre = 'b';
        // depuis l'état 1 un b
        ex->delta[1][1].etat = 1;
        ex->delta[1][1].lettre = 'a';

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

// TEST
// char clair[TAILLE_MAX_TEXTE] = "aaabbaba";
// char encode[TAILLE_MAX_TEXTE] ;
// transducteur* trans = exemple1();
// codeTransducteur(clair, encode, *trans);
// // printf("exemple 1 encode %s en %s \n",clair, encode);
// assert(strcmp(encode, "abaaabbb") == 0);
// libererTransducteur(trans);
// printf("TEST OK \n");

void inverserTransducteur(transducteur* trans){
    if (trans->inverse != NULL){return ;} // l inverse a déja été calculé

    transducteur * inv = initialiserTransducteur(trans->nbEtat, trans->nbLettre);

    for(int e = 0; e < trans->nbEtat ; e++){
        for(int l = 0; l < trans->nbLettre ; l++){
            inv->delta[e][trans->delta[e][l].lettre - 'a'].etat = trans -> delta[e][l].etat;
            inv->delta[e][trans->delta[e][l].lettre - 'a'].lettre = l + 'a';
        }
    }
    inv->inverse = trans;
    trans->inverse = inv;
}

void decodeTransducteur(char * messageEncode, char * messageDecode, transducteur * trans ){
    inverserTransducteur(trans);
    codeTransducteur(messageEncode, messageDecode, * (trans->inverse));
}

// char clair[TAILLE_MAX_TEXTE] = "ababbababbbbbababbbbbaaaaababa";
// char encode[TAILLE_MAX_TEXTE];
// char decode[TAILLE_MAX_TEXTE];
// transducteur* trans = exemple1();
// codeTransducteur(clair, encode, *trans);
// decodeTransducteur(encode, decode, trans);
// printf("exemple 1 encode %s en %s et decode en %s \n",clair, encode,decode);
// assert(strcmp(clair, decode) == 0);
// libererTransducteur(trans);
// printf("TEST OK \n");

bool estTableauDeVrai(bool * tab,int taille){
    for (int i =0; i<taille; i++ ){
        if (!tab[i]){return false;}
    }
    return true;
}

// bool tab1[] = {1,1,1,1,1};
// assert(estTableauDeVrai(tab1,5));
// bool tab2[] = {1,1,1,1,0};
// assert(!estTableauDeVrai(tab2,5));
// bool tab3[] = {0,1,1,1,1};
// assert(!estTableauDeVrai(tab3,5));
// printf("TEST OK\n");

bool estValideTranducteur(transducteur trans){ 
    bool * tab = malloc(sizeof(int) * trans.nbLettre);
    for (int etat = 0; etat<trans.nbEtat; etat++){
        // remplir le tableau de false
        for(int i = 0;i<trans.nbLettre; i++){
            tab[i] = false;
        }
        
        for(int i = 0;i<trans.nbLettre; i++){
            // verifier que la lettre existe
            if (trans.delta[etat][i].lettre - 'a' < 0 || trans.delta[etat][i].lettre - 'a' > trans.nbLettre - 1){
                free(tab);
                return false;
            }
            // mettre la case du tableau i a vrai ssi la lettre est presente dans les transitions 
            tab[trans.delta[etat][i].lettre-'a'] = true;
            // verification que l'état final existe
            if (trans.delta[etat][i].etat < 0 || trans.delta[etat][i].etat > trans.nbEtat - 1){
                free(tab);
                return false;
            }
        }
        if(!estTableauDeVrai(tab,trans.nbLettre)){
            free(tab);
            return false;
        }
    }
    free(tab);
    return true;
}

    // transducteur *trans1 = chargerTransducteur("transducteurFaux1");
    // assert(!estValideTranducteur(*trans1));
    // libererTransducteur(trans1);
    // transducteur *trans2 = chargerTransducteur("transducteurFaux2");
    // assert(!estValideTranducteur(*trans2));
    // libererTransducteur(trans2);
    // transducteur *trans3 = chargerTransducteur("transducteurFaux3");
    // assert(!estValideTranducteur(*trans3));
    // libererTransducteur(trans3);
    // transducteur *trans4 = chargerTransducteur("ex1");
    // assert(estValideTranducteur(*trans4));
    // libererTransducteur(trans4);
    // printf("TEST OK\n");


// ENvrai go le decaler dans aleatoire
transducteur* genererTransducteurAleatoire(int nombreEtat, int nombreLettre){
    transducteur *retour = initialiserTransducteur(nombreEtat,nombreLettre);
    
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// Go finir l'aleatoire

// Brut force

// Generation de transducteurs aleatoire 

// analyse des composantes connexes ou qui on une faible proba d etre quiter trop petite
// passage par les etats chauds

// identifier la proportion de faible 

// ameliorer le rendement ????

// int main(){
//     printf("TEST OK\n");

//     return 0;
// }