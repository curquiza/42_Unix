****************************
******* Projet ft_ls *******
****************************


Flags traités
-------------

Les basics :
- R : affichage récursif des files et de leurs contenus
- l : long format (dont gestion des ACL et attributs étendus)
- a : affichage files cachés
- t : tri par date de modification, le plus récent en tête
- r : renverse l'ordre

Les bonus :
- 1 : affiche un file par ligne, car gestion des colonnes prise en compte
- G : gestion des couleurs (pas exactement comme le vrai ls)
- S : tri par taille, le plus gros en tête. Annule le flag -t.
- T : affiche la date complète uniquement si le flag -l est activé.
- U : prise en compte de la date de création pour les flags -t et -l
- d : traite tous les arguments comme des files "non ouvrables"
- f : active le flag a et annule les flags de tri (y compris -r)
- u : prise en compte de la date de dernier acces pour les flags -t et -l


/!\ Ne fait pas comme le vrai ls
--------------------------------

- ./ft_ls ""
- Si les fonctions getpwuid et getgrgid ne fonctionnent pas, ft_ls ne traite
pas ce cas et n'affiche pas le numero de uid et/ou de gid à la place du nom
correspondant
- les colonnes sont gérées comme /bin/ls -G, c'est à dire avec des blanks et
non pas comme /bin/ls qui le gère avec des termcaps.
