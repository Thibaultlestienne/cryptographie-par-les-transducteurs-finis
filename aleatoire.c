#include "aleatoire.h"

void initialiserAleatoire(){
    srand(GRAINE);
}

int nombreAleatoire(int min, int max){ // loi uniforme
    return (rand() / (max-min))+min;
}

int inserer(int * tab, int k, int v){// insere la valeur v dans le k

}

int* permutationAleatoire(int n){//Renvoie une permutation de [|1,n|] choisis uniformement
    int * retour = malloc(sizeof(int)* n);
    for (int i = 0; i < n; i++){
        retour[i] =0;
    }
    for (int i = 0; i<n ; i++){
        
    }
    return retour;
}