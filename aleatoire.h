#ifndef ALEATOIRE
#define ALEATOIRE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include "constantes.h"
#include "transducteur.h"

#include "aleatoire.h"

void initialiserAleatoire();

int entierAleatoire(int min, int max);

void swapInt(int tab[],int i, int j);

void melangerUniformeTableau(int tab[], int taille);

void permutationUniforme(int tableau[], int n);

transducteur * TransducteurUniforme(int nbEtat, int nbLettre);

#endif