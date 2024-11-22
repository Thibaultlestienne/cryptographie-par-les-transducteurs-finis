#ifndef ANALYSE_FREQUENCE
#define ANALYSE_FREQUENCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define FICHIER "victorhugo.txt"

extern float FREQUENCETHEORIQUE[26];

char* enleverAccents(char* str);

void freqSimpleFichier(char* name_fich, float* tabfreq);

void freqSimpleTexte(char* texte, float* tabfreq);

void freqCoupleFichier(char* name_fich, float* tabfreq);

// float abso(float nb);

// int decode_cesar(char* nom_fcode, char* txt_etalon);

#endif //ANALYSE_FREQUENCE
