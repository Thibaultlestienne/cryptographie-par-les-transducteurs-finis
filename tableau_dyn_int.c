#include "tableau_dyn_int.h" 

tableau_dyn_int tableau_dyn_int_initialisation(int n) {
    tableau_dyn_int t;
    t.taille = n;
    t.nbelt = 0;
    t.tab = malloc(n*sizeof(int));
    if (t.tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    return t;
};

void tableau_dyn_int_agrandir(tableau_dyn_int* t) {
    int* tmp = malloc(2*t->taille*sizeof(int));
    if (tmp == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    int ntaille = 2*t->taille;
    for (int i=0; i<t->nbelt; i++) {
        tmp[i] = t->tab[i];
    };
    t->taille = ntaille;
    free(t->tab);
    t->tab = tmp;
};

void tableau_dyn_int_ajoute(tableau_dyn_int* t, int v) {
    if (t->taille == t->nbelt) {
        tableau_dyn_int_agrandir(t);
    };
    t->tab[t->nbelt] = v;
    t->nbelt += 1;
};

void tableau_dyn_int_vider(tableau_dyn_int* t) {
    free(t->tab);
    if (t->tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    } 
    t->taille = 1;
    t->nbelt = 0;
};

void tableau_dyn_int_supp(tableau_dyn_int* t){
    free(t->tab);

};

void tableau_dyn_int_affiche(tableau_dyn_int t) {
    printf("Tableau de taille %d avec %d elements\n", t.taille, t.nbelt);
    for (int i=0; i<t.nbelt; i++) {
        printf("\tDans la case : %d \t il y a : %d\n", i, t.tab[i]);
    };
};

int tableau_dyn_int_minimum(tableau_dyn_int dyntab){
    int min = dyntab.tab[0];
    for (int i = 1; i < dyntab.nbelt ; i++){
        if (dyntab.tab[i] < min){min = dyntab.tab[i];}
    }
    return min;
}

int tableau_dyn_int_maximum(tableau_dyn_int dyntab){
    int max = dyntab.tab[0];
    for (int i = 1; i < dyntab.nbelt ; i++){
        if (dyntab.tab[i] > max){max = dyntab.tab[i];}
    }
    return max;
}

int tableau_dyn_int_produit(tableau_dyn_int dyntab){
    int prod = dyntab.tab[0];
    for (int i = 1; i < dyntab.nbelt ; i++){
        prod = prod * dyntab.tab[i];
    }
    return prod;
}

/* Jeu de test 
int main() {
    tableau_dyn_int t = tableau_dyn_int_initialisation(10);
    for (int i=0; i<100; i++) {
        tableau_dyn_int_ajoute(&t, i);
    };
    tableau_dyn_int_affiche(&t);
    printf("min : %d \nmax : %d\n", dyn_tab_int_minimum(t), dyn_tab_int_maximum(t));
    tableau_dyn_int_supp(&t);
    return 0;
};
*/