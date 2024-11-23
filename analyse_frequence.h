#ifndef ANALYSE_FREQUENCE
#define ANALYSE_FREQUENCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "constantes.h"

extern float FREQUENCETHEORIQUE[26];

char* enleverAccentsEspacePonctuationMajuscule(char* str);

void freqSimpleFichier(char* name_fich, float tabfreq[26]);

void freqSimpleTexte(char* texte, float tabfreq[26]);

void freqCoupleFichier(char* name_fich, float tabfreq[26][26]);

#endif //ANALYSE_FREQUENCE
