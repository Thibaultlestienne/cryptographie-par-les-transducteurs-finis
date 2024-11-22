#include "vigenere.h"

void codeVigner(char* messageClaire, char* messageEncode, char* cle){
    int i_cle = 0, l_cle = strlen(cle);
    int taille = strlen(messageClaire);
    for (int i = 0; i < taille+1; i++) {
        messageEncode[i] = decalage_caractere(messageClaire[i], cle[i%l_cle]-'a');
    }
}

void decodeVignerAvecCle(char* messageEncode, char* messageClaire, char* cle){
    int i_cle = 0, l_cle = strlen(cle);
    int taille = strlen(messageEncode);
    for (int i = 0; i < taille+1; i++) {
        messageClaire[i] = decalage_caractere(messageEncode[i], -(cle[i%l_cle]-'a'));
    }
}

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

void recollerSousChaine(char *chaine, char * sousChaine, int taille, int modulo){
    int position = 0;
    for (int i = 0; sousChaine[i]!='\0'; i++)
    {
        chaine[position*taille+modulo] = sousChaine[position];
        position++;
    }
    sousChaine[position*taille+modulo] = '\0';
}

float indiceDeCoincidence(char * chaine, int tailleCle){
    float IC = 0;
    char sousChaine[TAILLEMAXMESSAGE];
    int sstaille;
    float tabFreq[26] = {0};
    for (int i = 0; i < tailleCle; i++){
        decouperEnSousChaine(chaine, sousChaine, tailleCle, i);
        int sstaille = strlen(sousChaine);
        freqSimpleTexte(sousChaine,tabFreq);
        float somme = 0;
        for (int i=0; i<26; i++){
            somme += ((tabFreq[i]*((tabFreq[i]*sstaille)-1))/(sstaille - 1));
        }
        IC += somme;
    }
    return (IC/tailleCle);
}

void decodeVignerSansCle(char* messageEncode, char* messageClaire, float seuil/*0,065 par défault*/){
    int taille_cle = 1;
    char sousChaine[TAILLEMAXMESSAGE];
    while(indiceDeCoincidence(messageEncode,taille_cle)<seuil && taille_cle<TAILLEMAXMESSAGE){
        printf("%d : %f\n",taille_cle,indiceDeCoincidence(messageEncode,taille_cle));
        taille_cle++;
    }
    for (int i = 0; i< taille_cle; i++){
        printf("test1\n");
        decouperEnSousChaine(messageEncode,sousChaine,taille_cle,i);
        printf("%s\n",sousChaine);
        int decalage = decodeCesarTexte(sousChaine);
        printf("decalage %d\n", decalage);

        for (int j = 0; sousChaine[j]!='\0'; j++){
            sousChaine[j] = decalage_caractere(sousChaine[j], -decalage);
        }

        recollerSousChaine(messageClaire,sousChaine,taille_cle,i);
    }

}

void facteurs_premiers(tableau_dyn_int *facteur, int n){
    int d = 2;
    while(n>1) {
        if(n%d==0) {
            tableau_dyn_int_ajoute(facteur, d);
            n=n/d;
        } else {
            d=d+1;
        }
    }
}

void intersecter_facteur_premier_2(tableau_dyn_int intersrection, tableau_dyn_int tab1, tableau_dyn_int tab2){}

void intersecter_facteur_premier(tableau_dyn_int intersection, tableau_dyn_int * liste_decomposition){ // renvoie les facteurs communs 
    return ; // necessite de d'abord les merges 2 a 2
}

int main(/*Mettre les trucs speciaux pour le rentrer dans le terminal*/){
    char message[TAILLEMAXMESSAGE];
    codeVigner("TESTERAAAAAAAAAAAAAAAAAA", message,"test");
    printf("message : %s ", message);
    decodeVignerAvecCle(message, message,"test");
    printf("message : %s ", message);
    decouperEnSousChaine("ABCDABCDABCDABCDABCDAB",message,4,3);
    printf("message : %s ", message);
    float tab[26];
    char message2[TAILLEMAXMESSAGE] = "ABCDABCDABCDABCDABCDAB";
    freqSimpleTexte(message2,tab);
    printf("IC : %f ", indiceDeCoincidence("unpetittestpourpeutetreavoirunbeauresultatentoutcasjespere",2));
    printf("\n");
    printf("IC : %f ", indiceDeCoincidence("jedhhirwqarrmzauwhvbomokrxuuhczybeqczvbskxsbeyxppqb",2));
    printf("\n");
    printf("\n%d\n\n\n",decodeCesarFichier(TEST,HUGO));
    decodeVignerSansCle("
    ",message2,0.065);
    //                   NetinquietepasellenarienpourlinstantParcontredesuejeseraisrelieaureseauFlorenceneseraplusTucomprendsjenepeuxpaslaisserFlorencemegenerdansmatacheEtpuiselleensaitbeaucouptropsurmoiIlarecommenceetrecommencePratiquementtoutlesordinateursexistantsfurentsoussoncontroleIlnelaissaitpasdetracenesemontraispasEtpuisiladecouvertlesdialoguesendirectviaInternetletelephonelavisioconferenceladomotique

    printf("%s",message2);
    return 0;
}