compiler_transducteur:
	gcc -g transducteur.c analyse_frequence.c fichier.c aleatoire.c -o ex -fsanitize=address

compiler_transducteur_sans_verification_memoire:
	gcc -g transducteur.c analyse_frequence.c fichier.c aleatoire.c -o ex

compiler_cesar:
	gcc -g cesar.c analyse_frequence.c -o ex

compiler_analyseFreq:
	gcc -g analyse_frequence.c -o ex

compiler_vigenere:
	gcc -g vigenere.c analyse_frequence.c cesar.c -o ex

compiler_aleatoire:
	gcc -g aleatoire.c -o ex

presentation:
	google-chrome "https://docs.google.com/presentation/d/119parnhLlwXbr45Fj8y0k48cPkYcSLTneXuT8fSEdWM/edit#slide=id.p"

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh
