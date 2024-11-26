#ifndef TRANSDUCTEUR
#define TRANSDUCTEUR

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constantes.h"
#include "analyse_frequence.h"

typedef struct {
    int etat;
    char lettre;
} transition ;

typedef struct {
    int nbEtat;
    int nbLettre;
    transition** delta;

}transducteur;


#endif //TRANSDUCTEUR
