/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:43:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 19:55:37 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_opt_d :
** Activation de l'opt d = affiche les dossiers comme des files "non ouvrables"
*/

void	ft_del_lstin(t_list **alst)
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

void	ft_del_structpath(t_path **tab)
{
	ft_strdel(&(*tab)->name);
	ft_del_lstin(&(*tab)->lst_in);
	free(*tab);
	*tab = NULL;
}

void	ft_opt_d(t_path **argpath, char *opt)
{
	int		i;
	int		j;

	if (opt['d'] == 0)
		return ;
	opt['R'] = 0;
	i = 0;
	j = 0;
	while (argpath[i])
	{
		if (argpath[i]->inside)
		{
			j = 0;
			while (argpath[i]->inside[j])
			{
				ft_del_structpath(&argpath[i]->inside[j]);
				j++;
			}
			free(argpath[i]->inside);
			argpath[i]->inside = NULL;
		}
		i++;
	}
}
