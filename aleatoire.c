#include "aleatoire.h"

void initialiserAleatoire(){
    srand(GRAINE);
}

// initialiserAleatoire();
// int n1 = entierAleatoire(1,100);
// sleep(2);
// initialiserAleatoire();
// int n2 = entierAleatoire(1,100);
// sleep(2);
// initialiserAleatoire();
// int n3 = entierAleatoire(1,100);
// // printf("%d // %d // %d\n",n1,n2,n3);
// assert(n1!=n2 || n2!=n3 || n1!=n3);
// printf("TEST OK \n");

int entierAleatoire(int min, int max){ // loi uniforme
    return (rand() % (max+1-min))+min;
}

// srand(0);// Graine 0 pour les tests
// int tab[12] = {0};
// for (int  i = 0; i< 1000000; i++ ){
//     tab[entierAleatoire(1,10)]++;
// }
// for (int k = 0; k< 12; k++ ){
//     printf("%d -> %d \n",k,tab[k]);
// }
// assert(tab[0] == 0);
// assert(tab[11] == 0);
// for (int k = 1; k< 11; k++ ){
//     assert( 99000 < tab[k] && tab[k] < 101000);
// }
// printf("test OK\n");
// return 0;

void swapInt(int tab[],int i, int j){
    int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

void melangerUniformeTableau(int tab[], int taille){
    for (int i =0; i< taille; i++){
        swapInt(tab, i, entierAleatoire(0, i));
    }
}

void permutationUniforme(int tableau[], int n){//Renvoie une permutation de [|0,n-1|] choisis uniformement
    for (int i = 0; i < n; i++){
        tableau[i] = i;
    }
    melangerUniformeTableau(tableau,n);
}

// //tester les permutaions aleatoires
// srand(0);// Graine 0 pour les tests
// int resultat[10][10] = {0} ;
// int tab[10] = {0};
// for (int  i = 0; i< 1000000; i++ ){
//     permutationUniforme(tab, 10);
//     for (int k = 0; k < 10; k++){
//         resultat[k][tab[k]]++;
//     }
// }

// for (int k = 0; k< 10; k++ ){
//     for (int l = 0; l< 10; l++ ){
//         //printf("%d %d -> %d \n",k,l, resultat[k][l] );
//         assert( 99000 < resultat[k][l] && resultat[k][l] < 101000);
//     }
// }
// printf("test OK\n");
// return 0;

transducteur * TransducteurUniforme(int nbEtat, int nbLettre){
    transducteur * retour = initialiserTransducteur(nbEtat, nbLettre);
    int* permutation = malloc(sizeof(int) * nbLettre);
    for (int i = 0; i<nbEtat; i++){
        permutationUniforme(permutation, nbLettre);
        for (int j = 0; j<nbLettre; j++){
            retour->delta[i][j].lettre = permutation[j] + 'a';
            retour->delta[i][j].etat = entierAleatoire(0, nbEtat-1);
        }
    }
    free(permutation);
    return retour;
}

// initialiserAleatoire();
// transducteur * trans = TransducteurUniforme(10000,26);
// assert(estValideTranducteur(*trans));
// enregistrerTransducteur(*trans,"alea");
// printf("test OK\n");
// libererTransducteur(trans);
// return 0;

// int main(){
//     initialiserAleatoire();

//     transducteur * trans = TransducteurUniforme(1000,26);
//     char claire[TAILLE_MAX_TEXTE] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//     char code[TAILLE_MAX_TEXTE];
//     char decode [TAILLE_MAX_TEXTE];

//     codeTransducteur(claire, code, *trans);
//     decodeTransducteur(code, decode, trans);

//     printf("claire : %s\n",claire);
//     printf("  code : %s\n",code);
//     printf("decode : %s\n",decode);

//     assert(estValideTranducteur(*trans));
//     enregistrerTransducteur(*trans,"alea");
//     printf("test OK\n");
//     libererTransducteur(trans);
//     return 0;
// }



    