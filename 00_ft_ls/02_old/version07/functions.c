/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:59:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/14 11:06:02 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;

	if (!s1 || !s2 || !s3)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(*tmp) * (ft_strlen(s1) + ft_strlen(s2)
													+ ft_strlen(s3) + 1))))
		return (NULL);
	ft_strcpy(tmp, s1);
	tmp = tmp + ft_strlen(s1);
	ft_strcpy(tmp, s2);
	tmp = tmp + ft_strlen(s2);
	ft_strcpy(tmp, s3);
	tmp = tmp - ft_strlen(s1) - ft_strlen(s2);
	return (tmp);
}

/*
** ft_swap_pathtab :
** Echange deux éléments (en position i et j) d'un tableau de t_path
*/

void	ft_swap_pathtab(t_path **tab, int i, int j)
{
	t_path	*tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

/*
** ft_pathtablen :
** Calcule la taille d'un tableau de type t_path. Le dernier élément est NULL.
*/

int		ft_pathtablen(t_path **tab)
{
	int		cpt;

	cpt = 0;
	if (!tab)
		return (0);
	while (tab[cpt])
		cpt++;
	return (cpt);
}

/*
** ft_isdir :
** Retourne 1 si la structure path passée en paramètre est un dossier ou un lien
** symbolique pointant sur un dossier, 0 sinon.
**
** Surement pas obligatoire car peut etre remplacé par path->error != 20
*/

int		ft_isdir(t_path *path)
{
	if (path->display == NULL)
		return (0);
	if (S_ISDIR(path->lstat.st_mode))
		return (1);
	if (S_ISLNK(path->lstat.st_mode))
	{
		if (S_ISDIR(path->stat.st_mode))
			return (1);
	}
	return (0);
}
