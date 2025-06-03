interface : 
	gcc -shared -o cpourpython.so -fPIC transducteur.c analyse_frequence.c fichier.c aleatoire.c maths.c francais.c cpourpython.c
	python3 interface.py

compiler_transducteur:
	gcc -g transducteur.c analyse_frequence.c fichier.c aleatoire.c maths.c francais.c -o ex -fsanitize=address -lm

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh
