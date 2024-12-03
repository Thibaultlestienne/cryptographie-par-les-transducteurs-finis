#ifndef TRANSDUCTEUR
#define TRANSDUCTEUR

typedef struct transition transition;
typedef struct transducteur transducteur;

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constantes.h"
#include "analyse_frequence.h"
#include "fichier.h"
#include "aleatoire.h"

 struct transition{
    int etat;
    char lettre;
};

struct transducteur{
    int nbEtat;
    int nbLettre;
    transition** delta; //[nbEtat][nbLettre]
    struct transducteur * inverse; // vaut NULL si non calculé
};

#include "transducteur.h"

transducteur* initialiserTransducteur(int nombreEtat, int nombreLettre);

void libererTransducteur(transducteur* trans);

transducteur* exemple1();

void codeTransducteur(char * messageClair, char * messageEncode, transducteur trans );

void inverserTransducteur(transducteur* trans);

void decodeTransducteur(char * messageEncode, char * messageDecode, transducteur * trans );

#endif //TRANSDUCTEUR
