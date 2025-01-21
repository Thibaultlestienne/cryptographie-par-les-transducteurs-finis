import ctypes
import tkinter as tk
from tkinter import filedialog

def ouvrirFichier():
    global fichier
    nom = filedialog.askopenfilename(initialdir="sources/transducteurs", filetypes=[("Fichiers transducteurs", "*.transducteur")])
    fichier = nom.split("/")[-1].split(".")[0]

def ecrireSortie(texte,zoneDeSortie):
    zoneDeSortie.config(state=tk.NORMAL)
    zoneDeSortie.delete("1.0", tk.END)
    zoneDeSortie.insert(tk.END, texte)
    zoneDeSortie.config(state=tk.DISABLED)

# Charger le fichier.so
lib = ctypes.CDLL('./cpourpython.so')

# Definir les fonctions
#fonction pour coder
lib.coderPythonTransducteur.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
lib.coderPythonTransducteur.restype = ctypes.c_void_p

def coderTransducteur(zoneDeSaisie,zoneDeSortie):
    global fichier
    clair = zoneDeSaisie.get("1.0", tk.END)
    if fichier:
        # Encodage
        fichierTypeC = ctypes.create_string_buffer(fichier.encode("utf-8"))
        clairTypeC = ctypes.create_string_buffer(clair.encode("utf-8"))
        encodeTypeC = ctypes.create_string_buffer(len(clair)+1)
        lib.coderPythonTransducteur(fichierTypeC, clairTypeC, encodeTypeC) 
        ecrireSortie(encodeTypeC.value.decode("utf-8"),zoneDeSortie)

#fonction pour decoder
lib.decoderPythonTransducteur.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
lib.decoderPythonTransducteur.restype = ctypes.c_void_p

def decoderTransducteur(zoneDeSaisie,zoneDeSortie) :
    global fichier
    if fichier:
        encode = zoneDeSaisie.get("1.0", tk.END)
        fichierTypeC = ctypes.create_string_buffer(fichier.encode("utf-8"))
        encodeTypeC = ctypes.create_string_buffer(encode.encode("utf-8"))
        decodeTypeC = ctypes.create_string_buffer(len(encode)+1)
        lib.decoderPythonTransducteur(fichierTypeC, encodeTypeC, decodeTypeC) 
        ecrireSortie(decodeTypeC.value.decode("utf-8"),zoneDeSortie)

#fonction pour generer
lib.genererTransducteurAleatoirePython.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_int]
lib.genererTransducteurAleatoirePython.restype = ctypes.c_void_p

def genererTransducteur(nbEtat, nbLettre):
    global fichier
    if fichier:
        fichierTypeC = ctypes.create_string_buffer(fichier.encode("utf-8"))
        lib.genererTransducteurAleatoirePython(fichierTypeC, nbEtat, nbLettre)

# Créer des buffers pour les arguments
#fichier = ctypes.create_string_buffer(b"ex1")