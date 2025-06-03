#ifndef CONSTANTES
#define CONSTANTES

////////////////////////////////////////////////////////////////////////
//Fichier chargé de le gestion de constantes globles
////////////////////////////////////////////////////////////////////////

//////////////////////////Textes//////////////////////////

//Fichiers
#define HUGO "sources/textes/victorhugo.txt"
#define PROUST "sources/textes/marcelproust.txt"
#define FICHIERPOURANALYSE HUGO
#define FICHIERPOURALEATOIRE PROUST

// Dur
#define TXTTEST "La cryptographie est une des disciplines de la cryptologie s'attachant à protéger des messages (assurant confidentialité, authenticité et intégrité) en s'aidant souvent de secrets ou clés. Elle se distingue de la stéganographie qui fait passer inaperçu un message dans un autre message alors que la cryptographie rend un message supposément inintelligible à autre que qui de droit."
//Pour le Vigenere
#define CLETEST "cle"
#define RESULTATATTENDUVIGNER "nlgtjtvzktltjtigdxwyifpwftwettntrgdhgweeccresnzkkpwcexcnlcyxcavqeiipvfpwopwulkgdeudytlrvnspqmfprvtentxglyvsipemetxgpxkyxgrvkeigywcthcyxuzyxprvoiupgtpxuzyewiuppnpwgomuemprygoinlwvpkcysicersmgbykqeketcdwgcmpltgcgwfropwulkgoepdyplyvciopwulkglpqcwsfinlgtjtvzktltjtitprffropwulkgdyrasupqgyxkympeinwmitfnpecfxtpuwpuwthgovqtx"

////////////////////////// Tailles //////////////////////////
#define TAILLE_MAX_TEXTE 100000
#define TAILLE_MAX_LIGNE 1000

////////////////////////// Gestion Fichier //////////////////////////
#define TAILLE_MAX_NOM_FICHIER 200
#define DOSSIERTRANSDUCTEUR "sources/transducteurs"
#define EXTENTIONTRANSDUCTEUR "transducteur"

////////////////////////// Aleatoire //////////////////////////
#define GRAINE time(NULL)

#endif