#ifndef CESAR
#define CESAR

////////////////////////////////////////////////////////////////////////
//Fichier chargé du codage decodage du code Cesar
////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "analyse_frequence.h"
#include "maths.h" 

char decalage_caractere(char c, int decalage);

void codeCesar(char* messageClaire, char* messageEncode, int decalage);

int decodeCesarTexte(char* TexteEncode, char* TexteDecode) ;

int decodeCesarFichier(char* nom_fcode, char* txt_etalon);

#endif