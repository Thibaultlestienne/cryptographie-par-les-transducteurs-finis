compiler_transducteur:
	gcc -g transducteur.c analyse_frequence.c -o ex -fsanitize=address

compiler_transducteur_sans_verification_memoire:
	gcc -g transducteur.c analyse_frequence.c -o ex

compiler_cesar:
	gcc -g cesar.c analyse_frequence.c -o ex

compiler_analyseFreq:
	gcc -g analyse_frequence.c -o ex

compiler_vigenere:
	gcc -g vigenere.c analyse_frequence.c cesar.c -o ex

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh
