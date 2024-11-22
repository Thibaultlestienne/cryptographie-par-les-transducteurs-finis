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

void code_cesar(char* messageClaire, char* messageEncode, int decalage){//nomFich
    FILE* entree = fopen(messageClaire, "r");
    FILE* sortie = fopen(messageEncode, "w");
    assert(entree != NULL && sortie != NULL);
    char line[1000];
    while(fscanf(entree, "%[^\n]\n", line) != EOF) {
        int taille = strlen(line);
        char linecode[taille+1];
        for (int i = 0; i < taille+1; i++) {
            linecode[i] = decalage_caractere(line[i], decalage);
            //printf("%d\n",decalage_caractere(line[i], decalage));
        }
        fprintf(sortie, "%s\n", linecode);
    }
    fclose(entree);
    fclose(sortie);
}

float abso(float nb) {
    if (nb < 0) {return (-1 * nb);}
    else {return nb;}
}

int decodeCesarFichier(char* nom_fcode, char* txt_etalon) {//nom de fichiers
    float freqEtal[26];
    float freq[26];
    freqSimpleFichier(txt_etalon, freqEtal);
    freqSimpleFichier(nom_fcode, freq);
    float difMin = 1000;
    int decMin = 0;
    for (int i = 0; i < 26; i++) {
        float dif = 0;
        for (int j = 0; j < 26; j++) {
            int indDec = i+j;
            if (indDec > 25) indDec -= 26;
            dif += abso(freqEtal[j] - freq[indDec]);
        }
        if (dif < difMin) {
            decMin = i;
            difMin = dif;
        }
    }
    return decMin;
}

int decodeCesarTexte(char* TexteEncode) {//nom de fichiers
    float freq[26];
    freqSimpleTexte(TexteEncode, freq);
    float difMin = 1000;
    int decMin = 0;
    for (int i = 0; i < 26; i++) {
        float dif = 0;
        for (int j = 0; j < 26; j++) {
            int indDec = i+j;
            if (indDec > 25) indDec -= 26;
            dif += abso(FREQUENCETHEORIQUE[j] - freq[indDec]);
        }
        if (dif < difMin) {
            decMin = i;
            difMin = dif;
        }
    }
    return decMin;
}

    // Pour tester facteurs_premiers
    // tableau_dyn_int facteur = tableau_dyn_int_initialisation(1);
    // facteurs_premiers(&facteur, 1545158560);
    // tableau_dyn_int_affiche(facteur);
    // assert(tableau_dyn_int_produit(facteur) == 1545158560);



