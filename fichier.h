#ifndef FICHIER
#define FICHIER

#include <stdlib.h>
#include <stdio.h>
#include "transducteur.h"
#include "constantes.h"

void enregistrerTransducteur(transducteur trans, char* nomFichier);

transducteur* chargerTransducteur(const char *nomFichier);

#endif //FICHIER