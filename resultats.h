#ifndef RESULTATS
#define RESULTATS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "transducteur.h"
#include "aleatoire.h"
#include "analyse_frequence.h"
#include "cesar.h"
#include "vigenere.h"

#define FREQUENCESIMPLEFRANCAIS false  // affiche les fréquences simples des lettres de l'alphabet
#define FREQUENCECOUPLEFRANCAIS true // affiche les fréquences des couples de lettres de l'alphabet
#define FREQUENCEDOUBLEFRANCAIS false  // affiche la probabilité que deux lettres succesives soient identiques

#define DECODERCESAR false 
#define AFFICHAGECESAR false
#define NOMBRETESTCESAR 100
#define TAILLEMESSAGECESAR 20

#define DECODERVIGENERE false
#define AFFICHAGEVIGENERE false
#define NOMBRETESTVIGENERE 5
#define TAILLECLEVIGENERE 100
#define TAILLEMESSAGEVIGENERE 10000


void codeVigenere(char* messageClaire, char* messageEncode, char* cle);
void decodeVigenereAvecCle(char* messageEncode, char* messageClaire, char* cle);
void decouperEnSousChaine(char *chaine, char * sousChaine, int taille, int modulo);
void recollerSousChaine(char *chaine, char * sousChaine, int taille, int modulo);
double indiceDeCoincidence(char * chaine, int tailleCle);
void decodeVigenereSansCle(char* messageEncode, char* messageClaire, double seuil/*0,065 par défault*/,char* cle);

#endif 