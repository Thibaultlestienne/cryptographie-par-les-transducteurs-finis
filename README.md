# Cryptographie à l'aide des Transducteurs

Voici mon TIPE autour de la problématique :

#### Comment les transducteurs peuvent-ils permettre un transfert d'informations sécurisé?

## Théorie

Le dossier [source/presentation](https://github.com/Thibaultlestienne/transducteurfini/blob/main/sources/presentation) détaille le fonctionnement du chiffre.

## Chiffrer à la main

La force du chiffre ainsi créé est d'être utilisable par un humain sans le secours d'un ordinateur : voir [source/presentation/presentation.pdf](https://github.com/Thibaultlestienne/transducteurfini/blob/main/sources/presentation/presentation.pdf)
 (Slides 42 à 48)

## Comment chiffrer avec le logiciel dans ce répertoire

Pour chiffrer<br>
1 - Taper make (ou make interface) dans le terminal<br>
2 - Choisir un transducteur en haut (par défaut choisir le transducteur.transducteur)<br>
3 - Si besoin générer une clé (!!! Cela efface le transucteur précédemment stocké dans le fichier !!!)<br>
4 - Taper votre message dans la zone de saisie en haut<br>
5 - Appuyer sur le bouton chiffrer<br>
6 - le message chiffré apparait dans la zone du bas<br>

Pour déchiffrer<br>
1 - Taper make (ou make interface) dans le terminal<br>
2 - Choisir le transducteur utilisé pour chiffrer (par défaut choisir le transducteur.transducteur)<br>
3 - Taper le message reçu dans la zone de saisie en haut<br>
4 - Appuyer sur le bouton déchiffrer<br>
5 - le message déchiffré apparait dans la zone du bas<br>
