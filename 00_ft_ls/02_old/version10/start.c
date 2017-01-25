/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 21:06:03 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/19 12:21:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_tab_path :
** Retourne l'adresse du pointeur du premier argument path (pas option) de ft_ls
** Peut renvoyer NULL <=> le seul argument de ls sera alors "."
*/

char	**ft_tab_path(int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp("--", av[i]) == 0)
		{
			if (av[i + 1])
				return (av + i + 1);
			return (NULL);
		}
		if (av[i][0] != '-' || ft_strcmp("-", av[i]) == 0)
			return (av + i);
		i++;
	}
	return (NULL);
}

/*
** ft_create_argpath :
** Créer un tableau de structure s_path à partir d'un double tableau de char
** passé en paramètre (le retour de ft_tab_path)
** Ce tableau de structure est trié par ordre ascii.
*/

t_path	**ft_create_argpath(char **arg, char *opt)
{
	t_path	**newtab;
	int		i;

	if (arg == NULL)
	{
		if (!(newtab = (t_path **)malloc(sizeof(*newtab) * 2)))
			return (NULL);
		*(newtab + 1) = NULL;
		*newtab = ft_new_structpath(".", "", opt);
		(*newtab)->inside = ft_new_inside(*newtab, opt);
		return (newtab);
	}
	if (!(newtab = (t_path **)malloc(sizeof(*newtab) * (ft_tablen(arg) + 1))))
		return (NULL);
	*(newtab + ft_tablen(arg)) = NULL;
	i = 0;
	while (arg[i])
	{
		newtab[i] = ft_new_structpath(arg[i], "", opt);
		newtab[i]->inside = ft_new_inside(newtab[i], opt);
		i++;
	}
	ft_sortascii_pathtab(newtab);
	return (newtab);
}

/*
** ft_start :
** Début de ft_ls = gestion des illegal options + remplissage de argpath
*/

void	ft_start(int ac, char **av, t_path ***argpath, char *opt)
{
	int		i;

	if (ft_fill_opt(opt, ac, av) == -1)
		exit(EXIT_FAILURE);
	*argpath = ft_create_argpath(ft_tab_path(ac, av), opt);
	i = 0;
	while ((*argpath)[i])
	{
		if ((*argpath)[i]->error != 0 && (*argpath)[i]->error != 20
			&& (*argpath)[i]->display == NULL)
		{
			ft_putstr_fd("ls: ", 2);
			ft_putstr_fd((*argpath)[i]->name, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror((*argpath)[i]->error), 2);
		}
		i++;
	}
}
