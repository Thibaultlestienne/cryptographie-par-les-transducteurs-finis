#include "cpourpython.h"
    
void coderPythonTransducteur(char* fichier, char* messageclaire, char* messageencode){
    transducteur * trans = chargerTransducteur(fichier);
    codeTransducteur(messageclaire,messageencode,*trans);
}

void decoderPythonTransducteur(char* fichier, char* messageencode, char* messagedecode){
    transducteur * trans = chargerTransducteur(fichier);
    decodeTransducteur(messageencode,messagedecode,trans);
}

void genererTransducteurAleatoirePython(char* fichier, int nbetat, int nblettre){
    transducteur * trans = TransducteurUniforme(nbetat,nblettre);
    while (nombreComposantesFortementConnexe(*trans) != 1){
        libererTransducteur(trans);
        trans = TransducteurUniforme(nbetat,nblettre);
    }
    enregistrerTransducteur(*trans, fichier);
}