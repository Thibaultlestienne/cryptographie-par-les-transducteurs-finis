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

void afficherTransducteur(transducteur trans){ 
    // nbEtat et nbLettre
    printf("nb Etat : %d, nb Lettre : %d\n", trans.nbEtat, trans.nbLettre);

    printf("Delta : \n");

    // delta
    for (int i = 0; i < trans.nbEtat; i++) {
        for (int j = 0; j < trans.nbLettre; j++) {
            printf("|%d %c\t", trans.delta[i][j].etat, trans.delta[i][j].lettre);
        }
        printf("|\n");
    }
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

void codeFichierTransducteur(char * nomFichierClair, char * nomFichierEncode, transducteur trans){
    FILE * fichierClair = fopen(nomFichierClair, "r");
    FILE * fichierEncode = fopen(nomFichierEncode, "w");
    assert(fichierClair != NULL);
    assert(fichierEncode != NULL);

    int etatActif = 0;
    char messageClair[TAILLE_MAX_LIGNE];
    char messageEncode[TAILLE_MAX_LIGNE];
    while(fscanf(fichierClair, " %[^\n]\n", messageClair) != EOF){
        enleverAccentsEspacePonctuationMajuscule(messageClair);
        int i = 0;
        for(;messageClair[i] != '\0'; i++){
            messageEncode[i] = trans.delta[etatActif][messageClair[i] - 'a'].lettre;
            etatActif = trans.delta[etatActif][messageClair[i] - 'a'].etat;
        }
        messageEncode[i] = '\0';
        fprintf(fichierEncode, "%s\n", messageEncode);
    }
    fclose(fichierClair);
    fclose(fichierEncode);
}

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

void parcoursProfondeurTransducteur(transducteur trans, int etat, bool * visite, int * ordre, int * indice){
    if(visite[etat]){return;}
    visite[etat] = true;
    for (int i = 0; i<trans.nbLettre; i++){
        parcoursProfondeurTransducteur(trans, trans.delta[etat][i].etat, visite, ordre, indice);
    }
    ordre[*indice] = etat;
    (*indice)++;
}

void parcoursGraphe(bool ** graphe, int sommet, bool * visite, int nbsommet){
    if(visite[sommet]){return;}
    visite[sommet] = true;
    for (int i = 0; i<nbsommet; i++){
        if(graphe[sommet][i]){
            parcoursGraphe(graphe, i, visite, nbsommet);
        }
    }
}

int nombreComposantesFortementConnexe(transducteur trans){ // comparer a la methode de tarjan
    // methode de Kosaraju

    // initialisation pour le premier parcours
    bool * visite = malloc(sizeof(bool)*trans.nbEtat);
    int * ordre = malloc(sizeof(int)*trans.nbEtat);
    int indice = 0;

    for (int i = 0; i < trans.nbEtat; i++){
        visite[i] = false;
    }
    
    // Premier parcours
    for(int i=0;i<trans.nbEtat;i++){
        parcoursProfondeurTransducteur(trans, i, visite, ordre, &indice);
    }
    
    // Initialisation pour le deuxième parcours

    for (int i = 0; i<trans.nbEtat; i++){
        visite[i] = false;
    }

    // Construction du graphe transpose

    bool ** transTranspose = malloc(sizeof(bool*)*trans.nbEtat);
    for(int i = 0;i<trans.nbEtat;i++){
        transTranspose[i] = malloc(sizeof(bool)*trans.nbEtat);
        for (int j = 0; j < trans.nbEtat; j++)
        {
            transTranspose[i][j] = false;
        }
        
    }

    for(int etat = 0; etat<trans.nbEtat; etat++){
        for(int lettre = 0; lettre<trans.nbLettre;lettre++){
            transTranspose[trans.delta[etat][lettre].etat][etat] = true;
        }
    }


    // 2eme parcours
    int nbcomposantes = 0;

    for (int i = trans.nbEtat - 1; i >= 0; i--){
        if (!visite[ordre[i]]){
            parcoursGraphe(transTranspose, ordre[i], visite, trans.nbEtat);
            nbcomposantes++;
        }
    }

    // liberer la memoire
    
    free(visite);
    free(ordre);

    // liberer le graphe transpose
    for(int i = 0; i<trans.nbEtat;i++){
        free(transTranspose[i]);
    }
    free(transTranspose);

    return nbcomposantes; // Retourne le nombre d'états visités
}

// transducteur * trans1 = chargerTransducteur("ex1");
// assert(nombreComposantesFortementConnexe(*trans1) == 1);
// libererTransducteur(trans1);
// transducteur * trans2 = chargerTransducteur("ex2");
// assert(nombreComposantesFortementConnexe(*trans2) == 3);
// libererTransducteur(trans2);
// printf("TEST OK\n");
// return 0;

int espaceMemoireTransducteur(transducteur trans){
    size_t tailleMemoire = sizeof(transducteur) + trans.nbEtat * sizeof(transition*) + trans.nbEtat * trans.nbLettre * sizeof(transition);
    if (trans.inverse != NULL) {
        tailleMemoire += sizeof(transducteur) + trans.inverse->nbEtat * sizeof(transition*) + trans.inverse->nbEtat * trans.inverse->nbLettre * sizeof(transition);
    }
    return tailleMemoire;
}

// initialiserAleatoire();
// transducteur * trans1 = TransducteurUniforme(1000,26);
// assert(estValideTranducteur(*trans1));
// inverserTransducteur(trans1);
// printf("taille memoire : %d\n", espaceMemoireTransducteur(*trans1));
// libererTransducteur(trans1);
// return 0;

void permuter(double frequenceSimple[26], double frequenceDouble[26][26], int a, int b) {
    double tmp = frequenceSimple[a];

    printf("---------------------------------------");
    printf("Permutation: %d %d\n", a, b);

    //afficher tab double
    for(int i = 0; i<26; i++){
        printf("%d\t|", i);
        for(int j = 0; j<26; j++){
            printf("%f | ",frequenceDouble[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");

    frequenceSimple[a] = frequenceSimple[b];
    frequenceSimple[b] = tmp;

    for(int i = 0; i < 26; i++) {
        tmp = frequenceDouble[a][i];
        frequenceDouble[a][i] = frequenceDouble[b][i];
        frequenceDouble[b][i] = tmp;
    }

    for(int i = 0; i<26; i++){
        printf("%d\t|", i);
        for(int j = 0; j<26; j++){
            printf("%f | ",frequenceDouble[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");


    for (int i = 0; i < 26; i++) {
        tmp = frequenceDouble[i][a];
        frequenceDouble[i][a] = frequenceDouble[i][b];
        frequenceDouble[i][b] = tmp;
    }

    for(int i = 0; i<26; i++){
        printf("%d\t|", i);
        for(int j = 0; j<26; j++){
            printf("%f | ",frequenceDouble[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");

}

transducteur * decoderTransducteur1EtatSansCle(char * texte){

    //////////////////// Preparation ////////////////////
    transducteur * retour = initialiserTransducteur(1,26);
    enleverAccentsEspacePonctuationMajuscule(texte);

    double frequenceSimpleTexte[26];
    freqSimpleTexte(texte, frequenceSimpleTexte);


    //////////////////// Ordre initiale ////////////////////
    int * ordreTexte;
    ordreTexte = triIndices(frequenceSimpleTexte, 26);
    int * ordreFrancais;
    ordreFrancais = triIndices(FREQUENCETHEORIQUE, 26);

    double * tmp = malloc(sizeof(double) * 26);
    for(int i = 0; i<26; i++){
        retour->delta[0][i].etat = 0;
        retour->delta[0][ordreTexte[i]].lettre = 'a'+ordreFrancais[i];
        tmp[ordreFrancais[i]] = frequenceSimpleTexte[ordreTexte[i]];
    }
    for(int i = 0; i<26; i++){
        frequenceSimpleTexte[i] = tmp[i];
    }
    free(tmp);

    char textePreDecode[TAILLE_MAX_TEXTE];
    codeTransducteur(texte, textePreDecode, *retour);    
    double frequenceCouple[26][26];
    freqCoupleTexte(textePreDecode, frequenceCouple);

    // for(int i = 0; i<26; i++){
    //     for(int j = 0; j<26; j++){
    //         printf("%c%c: %f \n", 'a' + i, 'a' + j, frequenceCouple[i][j]);
    //     }
    // }

    // Etape finale : Monte Carlo

    double evalution = indiceCoincidenceFrancaisGlobalV2(frequenceSimpleTexte, frequenceCouple);

    // AVANT
    printf("AVANT\n");
    
    printf("Indice simple : %f\n", indiceCoincidenceFrancaisSimple(frequenceSimpleTexte));
    printf("Indice double : %f\n", indiceCoincidenceFrancaisCouple(frequenceCouple));
    printf("Indice global : %f\n", indiceCoincidenceFrancaisGlobalV2(frequenceSimpleTexte, frequenceCouple));

    inverserTransducteur(retour);
    afficherTransducteur(*retour->inverse);

    for (int i = 0; i < 1; i++){
        // choisir 2 nombres entre 0 et 25 differents
        int a = rand() % 26;
        int b = rand() % 25;
        if (b >= a){b++;}
        permuter(frequenceSimpleTexte, frequenceCouple, a, b);
        double evalutionTmp = indiceCoincidenceFrancaisGlobalV2(frequenceSimpleTexte, frequenceCouple);
        if (evalutionTmp > evalution){ // on conserve la permutation e t on fait les changement adequats
            evalution = evalutionTmp;
            char lettretmp = retour->delta[0][a].lettre;
            retour->delta[0][a].lettre = retour->delta[0][b].lettre;
            retour->delta[0][b].lettre = lettretmp;
            printf ("permutation : %d %d evalution : %f\n", a, b, evalution);
        }
        else{ // on revient a la configuration initiale
            permuter(frequenceSimpleTexte, frequenceCouple, a, b);
            printf (" pas permutation : %d %d evalution : %f\n", a, b, evalution);
        }

    }

    // affichage

    // for (int i = 0; i < 26; i++){
    //     printf("Lettre %c : %f\n", 'a' + i, frequenceSimpleTexte[i]);
    // }

    printf("APRES\n");
    printf("Indice simple : %f\n", indiceCoincidenceFrancaisSimple(frequenceSimpleTexte));
    printf("Indice double : %f\n", indiceCoincidenceFrancaisCouple(frequenceCouple));
    printf("Indice global : %f\n", indiceCoincidenceFrancaisGlobalV2(frequenceSimpleTexte, frequenceCouple));

    // Translate the encrypted message with the transducteur
    char messageDecode[TAILLE_MAX_TEXTE];
    codeTransducteur(texte, messageDecode, *retour);

    // Analyze the frequency and display it
    double frequenceDoubleDecode[26][26];
    freqCoupleTexte(messageDecode, frequenceDoubleDecode);

    printf("Double frequency analysis of the decoded message:\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            printf("%c%c: %f %f\n", 'a' + i, 'a' + j, frequenceDoubleDecode[i][j], frequenceCouple[i][j]);
            if (frequenceDoubleDecode[i][j] - frequenceCouple[i][j] != 0) {
                printf("WARNING: The frequency of the couple %c%c is too differenta\n", 'a' + i, 'a' + j);
            }
        }
    }

    free(ordreFrancais);
    free(ordreTexte);
    return retour;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// Brut force

// analyse des composantes connexes ou qui on une faible proba d etre quiter trop petite

// passage par les etats chauds

// identifier la proportion de faible 

// ameliorer le rendement ????

int main(){
    initialiserAleatoire();
    transducteur * trans = TransducteurUniforme(1,26);
    char claire[TAILLE_MAX_TEXTE];
    char encode[TAILLE_MAX_TEXTE];
    texteAleatoireFrancais(claire, TAILLE_MAX_TEXTE / 11);
    codeTransducteur(claire, encode, *trans);
    afficherTransducteur(*trans);
    //printf("claire : %s\n",claire);
    //printf("  code : %s\n",encode);
    transducteur *test;
    test = decoderTransducteur1EtatSansCle(encode);
    test->inverse = NULL;
    inverserTransducteur(test);
    afficherTransducteur(*test->inverse);
    libererTransducteur(test);
    libererTransducteur(trans);
    return 0;
}
