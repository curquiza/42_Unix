/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:59:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/08 13:19:28 by curquiza         ###   ########.fr       */
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
** ft_sortascii_pathtab :
** Trie le tableau de structure s_path par ordre ascii
*/

void	ft_sortascii_pathtab(t_path **tab)
{
	int		i;
	t_path	*tmp;

	i = 0;
	if (tab)
	{
		while (tab[i + 1])
		{
			if (ft_strcmp(tab[i]->name, tab[i + 1]->name) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				i = -1;
			}
			i++;
		}
	}
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

/*
** ---------------------------------------------------------------------
** ---------------------------------------------------------------------
** ---------------------------------------------------------------------
*/

void	ft_del_lst_in(t_list **alst)
{
	t_list	*current;

	if (!alst)
		return ;
	current = *alst;
	while (current)
	{
		ft_strdel((char **)&current->content);
		free(current);
		current = current->next;
	}
	*alst = NULL;
}

/*
** A mon avis, pas top car supprime le randg du dessous aussi...
** Va poser problème pour les enchainements.
*/

void	ft_del_pathtab(t_path ***tab)
{
	int		i;
	int		j;
	t_path	*current;

	i = -1;
	while ((*tab)[++i])
	{
		ft_strdel(&(*tab)[i]->name);
		ft_strdel(&(*tab)[i]->display);
		(*tab)[i]->permerror = 0;
		ft_del_lst_in(&(*tab)[i]->lst_in);
		j = -1;
		while ((*tab)[i]->inside[++j])
		{
			current = (*tab)[i]->inside[j];
			ft_strdel(&current->name);
			ft_strdel(&current->display);
			current->permerror = 0;
			ft_del_lst_in(&current->lst_in);
		}
		free((*tab)[i]->inside);
		(*tab)[i]->inside = NULL;
	}
	free(*tab);
	*tab = NULL;
}
