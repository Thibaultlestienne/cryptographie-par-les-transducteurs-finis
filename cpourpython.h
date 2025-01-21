#ifndef CPOURPYTHON
#define CPOURPYTHON

#include "transducteur.h"
#include "aleatoire.h"

void coderPythonTransducteur(char* fichier, char* messageclaire, char* messageencode);

void decoderPythonTransducteur(char* fichier, char* messageencode, char* messagedecode);

void genererTransducteurAleatoirePython(char* fichier, int nbetat, int nblettre);

#endif // CPOURPYTHON