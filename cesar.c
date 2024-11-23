#include "cesar.h" 

char decalage_caractere(char c, int decalage){
    if (c >= 'A' && c <= 'Z' ){
        unsigned char encodage = c + decalage;
        if (encodage > 'Z'){return  encodage-26;}
        else if (encodage < 'A'){return  encodage+26;}
        else {return encodage;}
    }
    if (c >= 'a' && c <= 'z' ){
        unsigned char encodage = c + decalage;
        if (encodage > 'z'){return  encodage-26;}
        else if (encodage < 'a'){return encodage+26;}
        else {return encodage;}
    }
    return c;
}

// TEST
// assert(decalage_caractere('a', 3) == 'd');
// assert(decalage_caractere('z', 3) == 'c');
// assert(decalage_caractere('b',-5) == 'w');
// printf("TEST decalage_caractere -> OK \n");

void codeCesar(char* messageClaire, char* messageEncode, int decalage){
    int i = 0;
    enleverAccentsEspacePonctuationMajuscule(messageClaire);
    for (; messageClaire[i] != '\0'; i++) {
        messageEncode[i] = decalage_caractere(messageClaire[i], decalage);
        //printf("%d\n",decalage_caractere(line[i], decalage));
    }
    messageEncode[i] = '\0';
}

// TEST OK
// char clair[TAILLE_MAX_TEXTE] = "un petit texte ";
// char encode[TAILLE_MAX_TEXTE];
// codeCesar(clair,encode,1);
// printf("%s\n", encode);
// printf("TEST code_cesar -> OK \n");

float valeurAbsolue(float nb) {
    if (nb < 0) {return (-1 * nb);}
    else {return nb;}
}

// assert(valeurAbsolue (0) == 0);
// assert(valeurAbsolue (0.5) == 0.5);
// assert(valeurAbsolue (-1.5) == 1.5);
// printf("test ok \n");

int decodeCesarTexte(char* TexteEncode, char* TexteDecode) {//nom de fichiers
    float frequenceMessage[26];
    freqSimpleTexte(TexteEncode, frequenceMessage);
    int MeilleurDecalage = 0;
    float MeilleurDifference = __FLT_MAX__;
    for (int decalage = 0; decalage < 26; decalage++) {
        float difference = 0;
        for (int i = 0; i < 26; i++) {
            difference += valeurAbsolue(FREQUENCETHEORIQUE[i] - frequenceMessage[(decalage+i) % 26]);
        }
        if (difference < MeilleurDifference) {
            MeilleurDecalage = decalage;
            MeilleurDifference = difference;
        }
    }

    int j = 0;
    for (0; TexteEncode[j]!='\0'; j++){
        TexteDecode[j] = decalage_caractere(TexteEncode[j], -MeilleurDecalage);
    }
    TexteDecode[j] = '\0';

    return MeilleurDecalage;
}

// TEST OK
// char clair[TAILLE_MAX_TEXTE] = "La cryptographie est une des disciplines de la cryptologie s'attachant à protéger des messages (assurant confidentialité, authenticité et intégrité) en s'aidant souvent de secrets ou clés. Elle se distingue de la stéganographie qui fait passer inaperçu un message dans un autre message alors que la cryptographie rend un message supposément inintelligible à autre que qui de droit.";
// char encode[TAILLE_MAX_TEXTE];
// char decode[TAILLE_MAX_TEXTE];
// int decalage = 5;

// codeCesar(clair,encode,decalage);
// assert(decodeCesarTexte(encode,decode) == decalage);
// assert(strcmp(enleverAccentsEspacePonctuationMajuscule(clair),decode)==0);
// printf("%s\n", enleverAccentsEspacePonctuationMajuscule(clair));
// printf("%s\n", decode);
// printf("TEST code_cesar -> OK \n");

int main(){

    return 0;
}

