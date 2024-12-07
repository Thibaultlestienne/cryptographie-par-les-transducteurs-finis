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

int* permutationUniforme(int n){//Renvoie une permutation de [|0,n-1|] choisis uniformement
    int * retour = malloc(sizeof(int)* n);
    for (int i = 0; i < n; i++){
        retour[i] = i;
    }
    melangerUniformeTableau(retour,n);
    return retour;
}

int main(){
    // tester les permutaions aleatoires

}