/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:59:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/03 18:56:59 by curquiza         ###   ########.fr       */
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
	while (tab[i + 1] && tab[i + 1]->display == NULL)
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
		(*tab)[i]->used = 0;
		ft_del_lst_in(&(*tab)[i]->lst_in);
		j = -1;
		while ((*tab)[i]->inside[++j])
		{
			current = (*tab)[i]->inside[j];
			ft_strdel(&current->name);
			ft_strdel(&current->display);
			current->used = 0;
			ft_del_lst_in(&current->lst_in);
		}
		free((*tab)[i]->inside);
		(*tab)[i]->inside = NULL;
	}
	free(*tab);
	*tab = NULL;
}
