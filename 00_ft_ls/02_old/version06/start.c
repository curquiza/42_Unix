/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 21:06:03 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/13 19:04:03 by curquiza         ###   ########.fr       */
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

	ft_putendl("YOP");
	if (arg == NULL)
	{
		ft_putendl("Hello");
		if (!(newtab = (t_path **)malloc(sizeof(*newtab) * 2)))
			return (NULL);
		*(newtab + 1) = NULL;
		*newtab = ft_new_structpath(".", ".", opt);
		(*newtab)->inside = ft_new_inside(*newtab, opt);
		return (newtab);
	}
	ft_putendl("POP");
	if (!(newtab = (t_path **)malloc(sizeof(*newtab) * (ft_tablen(arg) + 1))))
		return (NULL);
	ft_putendl("POP2");
	*(newtab + ft_tablen(arg)) = NULL;
	i = 0;
	while (arg[i])
	{
		ft_putendl("POP3");
		newtab[i] = ft_new_structpath(arg[i], arg[i], opt);
		ft_putendl("POP4");
		newtab[i]->inside = ft_new_inside(newtab[i], opt);
		ft_putendl("POP5");
		i++;
	}
	ft_sortascii_pathtab(newtab);
	return (newtab);
}

/*
** ft_print_fileerror :
** affiche les messages d'erreur des fichiers inexistants.
*/

void	ft_print_fileerror(t_path **argpath)
{
	while (*argpath)
	{
		if ((*argpath)->error != 0 && (*argpath)->error != 20
			&& (*argpath)->display == NULL)
		{
			ft_putstr_fd("ls: ", 2);
			ft_putstr_fd((*argpath)->name, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror((*argpath)->error), 2);
		}
		argpath++;
	}
}

/*
** ft_start :
** Début de ft_ls = gestion des illegal options + remplissage de argpath
*/

void	ft_start(int ac, char **av, t_path ***argpath, char *opt)
{
	if (ft_fill_opt(opt, ac, av) == -1)
		exit(EXIT_FAILURE);
	*argpath = ft_create_argpath(ft_tab_path(ac, av), opt);
	ft_print_fileerror(*argpath);
}
