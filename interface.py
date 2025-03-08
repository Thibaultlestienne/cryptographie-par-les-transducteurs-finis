import tkinter as tk
from librairie import *

fenetre = tk.Tk()

fenetre.title("Securisation de données")
fenetre.geometry(f"{fenetre.winfo_screenwidth()}x{fenetre.winfo_screenheight()}")

# preparation des zonzs de texte
zoneDeSaisie = None
zoneDeSortie = None
zoneNomFichier = None
zoneNbEtats = None

# Zone de choix de fichier
zoneDeChoixFichier = tk.Frame(fenetre)
zoneDeChoixFichier.pack(pady=20)

# Bouton pour ouvrir un fichier
boutonDeSelectionDeFichier = tk.Button(zoneDeChoixFichier, text="Choisir un transducteur", command=lambda:ouvrirFichier(zoneNomFichier))
boutonDeSelectionDeFichier.pack(side=tk.LEFT,pady=20)

zoneNomFichier = tk.Text(zoneDeChoixFichier, height=1, width=25)
zoneNomFichier.pack(side=tk.LEFT, pady=20)
zoneNomFichier.config(state=tk.DISABLED)

# Zone pour permettre à l'utilisateur de saisir du texte
zoneDeSaisie = tk.Text(fenetre, height=10, width=120)
zoneDeSaisie.pack(pady=20)

# Zone de bouton
zoneDeBouton = tk.Frame(fenetre)
zoneDeBouton.pack(pady=20)

# Bouton pour coder
boutonCoder = tk.Button(zoneDeBouton, text="Coder", command=lambda:coderTransducteur(zoneDeSaisie,zoneDeSortie))
boutonCoder.pack(side=tk.LEFT, padx=10)

# Bouton pour decoder
boutonDecoder = tk.Button(zoneDeBouton, text="Decoder", command=lambda:decoderTransducteur(zoneDeSaisie,zoneDeSortie))
boutonDecoder.pack(side=tk.LEFT, padx=10)

# Bouton pour generer un transducteur
boutonGenerationDeCle = tk.Button(zoneDeBouton, text="Générer une clé", command=lambda:genererTransducteur(int(zoneNbEtats.get()),26))
boutonGenerationDeCle.pack(side=tk.LEFT, padx=10)

# Label nb etats
labelNbEtats = tk.Label(zoneDeBouton, text="Nombre d'états")
labelNbEtats.pack(side=tk.LEFT, padx=10)

# Zone pour saisir le nombre d'états
zoneNbEtats = tk.Entry(zoneDeBouton)
zoneNbEtats.pack(side=tk.LEFT, padx=10)
zoneNbEtats.insert(tk.END, 1000)


# Zone de sortie
zoneDeSortie = tk.Text(fenetre, height=10, width=120)
zoneDeSortie.pack(pady=20)
zoneDeSortie.config(state=tk.DISABLED)

fenetre.mainloop()
