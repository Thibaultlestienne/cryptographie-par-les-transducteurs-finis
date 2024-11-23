#include "analyse_frequence.h"

float FREQUENCETHEORIQUE[] = {0.088407, 0.010537, 0.031582, 0.035204, 0.171920, 0.011069, 0.009396, 0.009726, 0.075093, 0.005395, 0.000063, 0.059660, 0.028249, 0.067355, 0.051662, 0.026124, 0.011992, 0.064086, 0.075002, 0.076678, 0.063793, 0.018107, 0.000108, 0.003999, 0.003268, 0.001527};

// float somme = 0;
// for (int i = 0; i < 26; i++) {somme += FREQUENCETHEORIQUE[i];}
// printf("si OK  %f a peu près egal a 1", somme);

char* enleverAccentsEspacePonctuationMajuscule(char* str) {
    unsigned char* src = (unsigned char*)str;
    unsigned char* dst = src;

    while (*src) {
        if (*src == 0xC3) { // Détecter un caractère accentué UTF-8
            src++;
            switch (*src) {
                case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: // à á â ã ä å
                    *dst = 'a'; break;
                case 0xA8: case 0xA9: case 0xAA: case 0xAB: // è é ê ë
                    *dst = 'e'; break;
                case 0xAC: case 0xAD: case 0xAE: case 0xAF: // ì í î ï
                    *dst = 'i'; break;
                case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB6: // ò ó ô õ ö
                    *dst = 'o'; break;
                case 0xB9: case 0xBA: case 0xBB: case 0xBC: // ù ú û ü
                    *dst = 'u'; break;
                case 0xBD: case 0xBF: // ý ÿ
                    *dst = 'y'; break;
                case 0xA7: // ç
                    *dst = 'c'; break;
                case 0xB1: // ñ
                    *dst = 'n'; break;
                default:
                    src++; // Ignorer caractères inconnus
                    continue;
            }
        } else if ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z')) {
            // Convertir en minuscule si majuscule
            *dst = (*src >= 'A' && *src <= 'Z') ? (*src + 32) : *src;
        } else if (*src == '\0') {
            // Convertir en minuscule si majuscule
            *dst = '\0';
        } else {
            // Ignorer les espaces, chiffres et caractères de ponctuation
            src++;
            continue;
        }
        src++;
        dst++;
    }
    *dst = '\0'; // Terminer la chaîne
    return (char*)str;
}

// TEST - OK
// char test[TAILLE_MAX_TEXTE] = "test  éçèè - A";
// printf("%s",enleverAccentsEspacePonctuationMajuscule(test));

void freqSimpleFichier(char* name_fich, float tabfreq[26]) {
    FILE* fichier = fopen(name_fich, "r");
    assert(fichier != NULL);
    int tab[26] = {0};
    char line[TAILLE_MAX_TEXTE];
    int nb_char = 0;
    while(fscanf(fichier, "%[^\n]\n", line) != EOF) {
        char* ligneSans = enleverAccentsEspacePonctuationMajuscule(line);
        for (int i = 0; ligneSans[i] != '\0' ; i++) {
            if (ligneSans[i] >= 'a' && ligneSans[i] <= 'z') {
                tab[ligneSans[i] - 'a'] += 1;
                nb_char ++;
            }
            if (ligneSans[i] >= 'A' && ligneSans[i] <= 'Z') {
                tab[ligneSans[i] - 'A'] += 1;
                nb_char ++;
            }
        }
    }
    fclose(fichier);
    for (int i = 0; i < 26; i ++) tabfreq[i] = (float)tab[i]/nb_char;
}


// TEST
// float tab[26];
// freqSimpleFichier("victorhugo.txt", tab);
// for (int i = 0; i < 26; i ++) {
//     printf("Fréquence de %c : %f\n", i + 'a', tab[i]);
// }

void freqSimpleTexte(char* texte, float tabfreq[26]) {
    int tab[26] = {0};
    int nb_char = 0;
    char * texteSansAccents = enleverAccentsEspacePonctuationMajuscule(texte);
    int taille = strlen(texteSansAccents);
    for (int i = 0; texteSansAccents[i] != '\0' ; i++) {
        if (texteSansAccents[i] >= 'a' && texteSansAccents[i] <= 'z') {
            tab[texteSansAccents[i] - 'a'] += 1;
            nb_char ++;
        }
        if (texteSansAccents[i] >= 'A' && texteSansAccents[i] <= 'Z') {
            tab[texteSansAccents[i] - 'A'] += 1;
            nb_char ++;
        }
    }
    for (int i = 0; i < 26; i ++) tabfreq[i] = (float)tab[i]/taille;
}

// TEST - OK
// char test[TAILLE_MAX_TEXTE] = "test  2 é 5 t tot 12car";
// float tab[26] = {0}; 
// freqSimpleTexte(test, tab);
// for (int i = 0; i < 26; i ++) {
//     printf("Fréquence de %c : %f\n", i + 'a', tab[i]);
// }

void freqCoupleFichier(char* name_fich, float tabfreq[26][26]) {
    FILE* fichier = fopen(name_fich, "r");
    assert(fichier != NULL);
    int tab[26][26] = {0};
    char line[TAILLE_MAX_TEXTE];
    int nb_couple = 0;
    while(fscanf(fichier, "%[^\n]\n", line) != EOF) {
        char* ligneSans = enleverAccentsEspacePonctuationMajuscule(line);
        for (int i = 0; ligneSans[i+1] != '\0'; i++) {
            int premiere_lettre = 0;
            int deuxieme_lettre = 0;

            if (ligneSans[i] >= 'A' && ligneSans[i] <= 'Z') {
                premiere_lettre = ligneSans[i] - 'A';
            }
            else if (ligneSans[i] >= 'a' && ligneSans[i] <= 'z') {
                premiere_lettre = ligneSans[i] - 'a';
            }
            if (ligneSans[i+1] >= 'A' && ligneSans[i+1] <= 'Z') {
                deuxieme_lettre += ligneSans[i+1] - 'A';
            }
            else if (ligneSans[i+1] >= 'a' && ligneSans[i+1] <= 'z') {
                deuxieme_lettre += ligneSans[i+1] - 'a';
            }
            nb_couple ++;
            tab[premiere_lettre][deuxieme_lettre] += 1;
        }
    }
    fclose(fichier);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            tabfreq[i][j] = (float)tab[i][j]/nb_couple;
        }
    }
}

//TEST
// float tab[26][26];
// freqCoupleFichier("victorhugo.txt", tab);
// for (int i = 0; i < 26; i ++) {
//     for (int j = 0; j < 26; j ++) {
//         printf("Fréquence de %c%c : %f\n", i + 'a', j + 'a', tab[i][j]);
//     }
// }


// int main(int argc, char const *argv[])
// {
// }