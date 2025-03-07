#ifndef ANALYSE_FREQUENCE
#define ANALYSE_FREQUENCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "constantes.h"

extern double FREQUENCETHEORIQUE[26];
extern double FREQUENCECOUPLETHEORIQUE[26][26];

void enleverAccentsEspacePonctuationMajuscule(char* str);

void freqSimpleFichier(char* name_fich, double tabfreq[26]);

void freqSimpleTexte(char* texte, double tabfreq[26]);

void freqCoupleFichier(char* name_fich, double tabfreq[26][26]);

void freqCoupleTexte(char* texte, double tabfreq[26][26]);

#endif //ANALYSE_FREQUENCE
