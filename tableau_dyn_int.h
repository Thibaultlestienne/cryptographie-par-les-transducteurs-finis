#ifndef TABLEAU_DYN_INT
#define TABLEAU_DYN_INT

#include <stdlib.h>
#include <stdio.h>


// Structure des tableaux dynamiques 
typedef struct tableau_dyn_int {
    int taille; // nb de case dans le tableau
    int nbelt; // nb element dans le tableau
    int* tab; // le tableau
} tableau_dyn_int;

tableau_dyn_int tableau_dyn_int_initialisation(int n); // initialise un tableau dynamique de taille n

void tableau_dyn_int_agrandir(tableau_dyn_int* t); // double la taille du tableau dynamique

void tableau_dyn_int_ajoute(tableau_dyn_int* t, int v); // ajoute un element au tableau dynamique

void tableau_dyn_int_vider(tableau_dyn_int* t);  // met toutes les valeurs du tableau dynamique a 0

void tableau_dyn_int_supp(tableau_dyn_int* t);   // libere un tableau dynamique

void tableau_dyn_int_affiche(tableau_dyn_int t);// affiche le tableau dynamique

int tableau_dyn_int_minimum(tableau_dyn_int dyntab); // renvoie le minimum des elements du tableau dynamique

int tableau_dyn_int_maximum(tableau_dyn_int dyntab); // renvoie le maximum des elements du tableau dynamique

int tableau_dyn_int_produit(tableau_dyn_int dyntab); // renvoie le produit des elements du tableau dynamique

#endif // TABLEAU_DYN_INT