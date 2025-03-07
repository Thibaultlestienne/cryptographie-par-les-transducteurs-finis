#ifndef FRANCAIS
#define FRANCAIS
#define TAILLE_MESSAGE 5000

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "analyse_frequence.h"
#include "aleatoire.h"
#include "maths.h"

double indiceCoincidenceFrancaisSimple(double freqSimple[26]);

double indiceCoincidenceFrancaisCouple(double freqDouble[26][26]);

double indiceCoincidenceFrancaisGlobal(double freqSimple[26], double freqDouble[26][26]);

double indiceCoincidenceFrancaisGlobalV2(double freqSimple[26], double freqDouble[26][26]);


#endif 