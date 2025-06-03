#include "vigenere.h" 

void codeVigenere(char* messageClaire, char* messageEncode, char* cle){
    char message[TAILLE_MAX_TEXTE];
    enleverAccentsEspacePonctuationMajuscule(messageClaire);
    int i_cle = 0, l_cle = strlen(cle);
    int i = 0;
    for (;messageClaire[i] != '\0'; i++) {
        messageEncode[i] = decalage_caractere(messageClaire[i], cle[i%l_cle]-'a');
    }
    messageEncode[i] = '\0';
}

// TEST OK
// char message[TAILLE_MAX_TEXTE] = TXTTEST;
// char encode[TAILLE_MAX_TEXTE];
// codeVigenere(message, encode,CLETEST);
// assert(strcmp(encode, RESULTATATTENDUVIGNER) == 0);
// printf("TEST OK\n");

void decodeVigenereAvecCle(char* messageEncode, char* messageClaire, char* cle){
    int i_cle = 0, l_cle = strlen(cle);
    int taille = strlen(messageEncode);

    enleverAccentsEspacePonctuationMajuscule(messageEncode);

    int i = 0;
    for (; i < taille; i++) {
        messageClaire[i] = decalage_caractere(messageEncode[i], -(cle[i%l_cle]-'a'));
    }
    messageEncode[i] = '\0';
}

// TEST OK
// char clair[TAILLE_MAX_TEXTE] = TXTTEST;
// char encode[TAILLE_MAX_TEXTE] = RESULTATATTENDUVIGNER;
// char decode[TAILLE_MAX_TEXTE];
// decodeVigenereAvecCle(encode, decode,CLETEST);
// enleverAccentsEspacePonctuationMajuscule(clair);
// assert(strcmp(decode, clair )== 0);
// printf("TEST OK\n");

void decouperEnSousChaine(char *chaine, char * sousChaine, int taille, int modulo){
    int position = 0;
    for (int i = 0; chaine[i]!='\0'; i++)
    {
        if(i%taille == modulo){
            sousChaine[position] = chaine[i];
            position++;
        }
    }
    sousChaine[position] = '\0';
}

// TEST OK
// char ssChaine[TAILLE_MAX_TEXTE];
// decouperEnSousChaine("abcdabcdabcdabcdab",ssChaine,4,3);
// assert(strcmp(ssChaine, "dddd" )== 0);
// printf("TEST OK");

void recollerSousChaine(char *chaine, char * sousChaine, int taille, int modulo){
    int position = 0;
    for (int i = 0; sousChaine[i]!='\0'; i++)
    {
        chaine[position*taille+modulo] = sousChaine[position];
        position++;
    }
    sousChaine[position*taille+modulo] = '\0';
}

// char ssChaine1[TAILLE_MAX_TEXTE] = "aaaa";
// char ssChaine2[TAILLE_MAX_TEXTE] = "bbb";
// char chaine[TAILLE_MAX_TEXTE];
// recollerSousChaine(chaine,ssChaine1,2,0);
// recollerSousChaine(chaine,ssChaine2,2,1);
// assert(strcmp(chaine, "abababa" )== 0);
// printf("TEST OK");

double indiceDeCoincidence(char * chaine, int tailleCle){
    double IC = 0;
    char sousChaine[TAILLE_MAX_TEXTE];
    int tailleSousChaine;
    double tabFreq[26] = {0};
    for (int i = 0; i < tailleCle; i++){
        decouperEnSousChaine(chaine, sousChaine, tailleCle, i);
        int tailleSousChaine = strlen(sousChaine);
        freqSimpleTexte(sousChaine,tabFreq);
        double somme = 0;
        for (int i=0; i<26; i++){
            somme += ((tabFreq[i]*((tabFreq[i]*tailleSousChaine)-1))/(tailleSousChaine - 1));
        }
        IC += somme;
    }
    return (IC/tailleCle);
}

void decodeVigenereSansCle(char* messageEncode, char* messageClaire, double seuil/*0,065 par défault*/,char* cle){
    int taille_cle = 1;
    char sousChaineEncode[TAILLE_MAX_TEXTE];
    char sousChaineDecode[TAILLE_MAX_TEXTE];

    while(indiceDeCoincidence(messageEncode,taille_cle)<seuil && taille_cle<TAILLE_MAX_TEXTE){
        taille_cle++;
    }
    for (int i = 0; i< taille_cle; i++){
        decouperEnSousChaine(messageEncode,sousChaineEncode,taille_cle,i);
        int decalage = decodeCesarTexte(sousChaineEncode,sousChaineDecode);
        recollerSousChaine(messageClaire,sousChaineDecode,taille_cle,i);
        cle[i] = 'a'+decalage;
    }
    cle[taille_cle] = '\0';

}

// char clair[TAILLE_MAX_TEXTE] = TXTTEST;
// char encode[TAILLE_MAX_TEXTE];
// char decode[TAILLE_MAX_TEXTE];
// char cle[TAILLE_MAX_TEXTE];

// codeVigenere(clair,encode,CLETEST);
// decodeVigenereSansCle(encode,decode,0.065,cle);
// assert(strcmp(cle, CLETEST) == 0);
// assert(strcmp(decode, clair) == 0);
// printf("TEST OK\n");

// int main(){
//     char clair[TAILLE_MAX_TEXTE] = TXTTEST;
//     char encode[TAILLE_MAX_TEXTE];
//     char decode[TAILLE_MAX_TEXTE];
//     char cle[TAILLE_MAX_TEXTE];

//     codeVigenere(clair,encode,CLETEST);
//     decodeVigenereSansCle(encode,decode,0.065,cle);
//     assert(strcmp(cle, CLETEST) == 0);
//     assert(strcmp(decode, clair) == 0);
//     printf("TEST OK\n");

// return 0;
// }
