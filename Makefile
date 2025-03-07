compiler_transducteur:
	gcc -g transducteur.c analyse_frequence.c fichier.c aleatoire.c maths.c -o ex -fsanitize=address

compiler_transducteur_sans_verification_memoire:
	gcc -g transducteur.c analyse_frequence.c fichier.c aleatoire.c -o ex

compiler_cesar:
	gcc -g cesar.c analyse_frequence.c maths.h -o ex

compiler_analyseFreq:
	gcc -g analyse_frequence.c -o ex

compiler_vigenere:
	gcc -g vigenere.c analyse_frequence.c cesar.c -o ex

compiler_francais:
	gcc -g francais.c analyse_frequence.c aleatoire.c transducteur.c maths.c -lm -o ex

compiler_resultats:
	gcc -g resultats.c cesar.c vigenere.c analyse_frequence.c transducteur.c aleatoire.c maths.c -o ex

compiler_cpourpython :
	gcc -shared -o cpourpython.so -fPIC transducteur.c analyse_frequence.c fichier.c aleatoire.c cpourpython.c 

interface : compiler_cpourpython
	python3 interface.py

presentation:
	google-chrome "https://docs.google.com/presentation/d/119parnhLlwXbr45Fj8y0k48cPkYcSLTneXuT8fSEdWM/edit#slide=id.p"

mcot:
	google-chrome "https://docs.google.com/document/d/1JvuZWCaYegk4VOUWGQ-JlJLkBKNPkktJAUQF_uu-zko/edit?tab=t.0"

# Génération du PDF à partir du fichier LaTeX
pdf: 
	pdflatex -output-directory="sources/preuve et reflexion" "sources/preuve et reflexion/formules.tex"
	rm -f "sources/preuve et reflexion"/*.aux "sources/preuve et reflexion"/*.log "sources/preuve et reflexion"/*.out "sources/preuve et reflexion"/*.toc

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh
