/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:09:11 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/14 19:53:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

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
** A mon avis, pas top car supprime le rang du dessous aussi...
** Va poser problème pour les enchainements.
*/

/*void	ft_del_pathtab(t_path ***tab)
{
	int		i;
	int		j;
	t_path	*current;

	i = -1;
	while ((*tab)[++i])
	{
		ft_strdel(&(*tab)[i]->name);
		ft_strdel(&(*tab)[i]->display);
		(*tab)[i]->error = 0;
		ft_del_lst_in(&(*tab)[i]->lst_in);
		j = -1;
		while ((*tab)[i]->inside[++j])
		{
			current = (*tab)[i]->inside[j];
			ft_strdel(&current->name);
			ft_strdel(&current->display);
			current->error = 0;
			ft_del_lst_in(&current->lst_in);
		}
		free((*tab)[i]->inside);
		(*tab)[i]->inside = NULL;
	}
	free(*tab);
	*tab = NULL;
}*/

void	ft_del_pathtab(t_path ***tab)
{
	int		i;

	i = -1;
	while ((*tab)[++i])
	{
		ft_strdel(&(*tab)[i]->name);
		ft_strdel(&(*tab)[i]->display);
		(*tab)[i]->error = 0;
		ft_del_lst_in(&(*tab)[i]->lst_in);
	}
	free(*tab);
	*tab = NULL;
}
