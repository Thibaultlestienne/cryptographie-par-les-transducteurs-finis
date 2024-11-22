#include "analyse_frequence.h"

float FREQUENCETHEORIQUE[] = {0.084, 0.006, 0.0303, 0.0418, 0.1726, 0.0112, 0.01027, 0.0092, 0.0734, 0.0031, 0.0005, 0.0601, 0.0296, 0.0713, 0.0526, 0.0301, 0.0099, 0.0655, 0.0808, 0.0707, 0.0574, 0.0132, 0.0004, 0.0045, 0.003, 0.0012};

char* enleverAccents(char* str) {
    unsigned char* p = (unsigned char*)str;
    unsigned char* src = p;
    unsigned char* dst = p;

    while (*src) {
        if (*src == 0xC3) { // Caractère accentué UTF-8 détecté
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
                    dst++; // On copie le caractère non accentué tel quel
                    continue;
            }
        } else {
            *dst = *src;
        }
        src++;
        dst++;
    }
    *dst = '\0'; // Terminer la chaîne correctement
    return str;
}



void freqSimpleFichier(char* name_fich, float* tabfreq) {
    FILE* fichier = fopen(name_fich, "r");
    assert(fichier != NULL);
    int tab[26] = {0};
    char line[200];
    int nb_char = 0;
    while(fscanf(fichier, "%[^\n]\n", line) != EOF) {
        char* ligneSans = enleverAccents(line);
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

void freqSimpleTexte(char* texte, float* tabfreq) {
    int tab[26] = {0};
    int nb_char = 0;
    char * texteSansAccents = enleverAccents(texte);
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


void freqCoupleFichier(char* name_fich, float* tabfreq) {
    FILE* fichier = fopen(name_fich, "r");
    assert(fichier != NULL);
    int tab[26*26] = {0};
    char line[200];
    int nb_couple = 0;
    while(fscanf(fichier, "%[^\n]\n", line) != EOF) {
        char* ligneSans = enleverAccents(line);
        for (int i = 0; ligneSans[i+1] != '\0'; i++) {

            int ind_couple = 0;
            int indic = 0; //0 signifie 0 lettres dans le couple
            if (ligneSans[i] >= 'A' && ligneSans[i] <= 'Z') {
                ind_couple = ligneSans[i] - 'A';
                indic++;
            }
            else if (ligneSans[i] >= 'a' && ligneSans[i] <= 'z') {
                ind_couple = ligneSans[i] - 'a';
                indic++;
            }
            if (ligneSans[i+1] >= 'A' && ligneSans[i+1] <= 'Z') {
                ind_couple += 26 * (ligneSans[i+1] - 'A');
                indic++;
            }
            else if (ligneSans[i+1] >= 'a' && ligneSans[i+1] <= 'z') {
                ind_couple += 26 * (ligneSans[i+1] - 'a');
                indic++;
            }
            if (indic == 2) {
                nb_couple ++;
                tab[ind_couple] += 1;
            }
            ind_couple = 0;
            indic = 0;
        }
    }
    fclose(fichier);
    for (int i = 0; i < 26 * 26; i++) tabfreq[i] = (float)tab[i]/nb_couple;
}

// int main(int argc, char const *argv[])
// {
//     float tab2[26];
//     float tabfreq[26*26];
//     freqSimple(TEST, tab2);
//     freqCouple(TEST, tabfreq);
//     for (int i = 0; i < 26*26; i++) {
//         printf("(%c,%c) : %f\n", i - (i/26)*26 + 'a', i/26 + 'a', tabfreq[i]);
//     }
//     for (int i = 0; i < 26; i ++) {
//         printf("Fréquence de %c : %f\n", i + 'a', tab2[i]);
//     }
//     printf("\n");
// }