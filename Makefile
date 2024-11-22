# Déclaration de la cible principale : compile le projet
compiler_cesar:
	gcc -g cesar.c analyse_frequence.c -o ex

compiler_vigenere:
	gcc -g vigenere.c analyse_frequence.c tableau_dyn_int.c cesar.c -o ex

# compile avec un debuger pour la memoire
compiler_avec_verification_memoire:
	gcc -g cesar.c tableau_dyn_int.c -o cesar -fsanitize=address -g

# Règle pour nettoyer le programme
nettoyer:
	rm -f cesar

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh
