import tkinter as tk
from librairie import *

fenetre = tk.Tk()

fenetre.title("Securisation de données")
fenetre.geometry(f"{fenetre.winfo_screenwidth()}x{fenetre.winfo_screenheight()}")

# preparation des zonzs de texte
zoneDeSaisie = None
zoneDeSortie = None

# Bouton pour ouvrir un fichier
boutonDeSelectionDeFichier = tk.Button(fenetre, text="Choisir un transducteur", command=ouvrirFichier)
boutonDeSelectionDeFichier.pack(pady=20)

# Zone pour permettre à l'utilisateur de saisir du texte
zoneDeSaisie = tk.Text(fenetre, height=10, width=120)
zoneDeSaisie.pack(pady=20)

# Zone de bouton
ZoneDeBouton = tk.Frame(fenetre)
ZoneDeBouton.pack(pady=20)

# Bouton pour coder
boutonCoder = tk.Button(ZoneDeBouton, text="Coder", command=lambda:coderTransducteur(zoneDeSaisie,zoneDeSortie))
boutonCoder.pack(side=tk.LEFT, padx=10)

# Bouton pour decoder
boutonDecoder = tk.Button(ZoneDeBouton, text="Decoder", command=lambda:decoderTransducteur(zoneDeSaisie,zoneDeSortie))
boutonDecoder.pack(side=tk.LEFT, padx=10)

# Bouton pour generer un transducteur
boutonGenerationDeCle = tk.Button(ZoneDeBouton, text="Générer une clé", command=lambda:genererTransducteur(1000,26))
boutonGenerationDeCle.pack(side=tk.LEFT, padx=10)

# Zone de sortie
zoneDeSortie = tk.Text(fenetre, height=10, width=120)
zoneDeSortie.pack(pady=20)
zoneDeSortie.config(state=tk.DISABLED)

fenetre.mainloop()
