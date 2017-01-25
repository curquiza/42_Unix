version finale, partie obligatoire finie
Pas de norme
La fonction ft_get_link boucle sur readlink donc :
- est précise, malloc pile ce qu'il faut
- fait perdre énormément de temps
=> va être enlevé dans la version finale
