/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/03 19:24:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

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
			return (av + i + 1);
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

t_path	**ft_create_argpath(char **arg)
{
	t_path	**newtab;
	int		i;

	if (arg == NULL)
	{	
		if (!(newtab = (t_path **)malloc(sizeof(*newtab) * 2)))
			return (NULL);
		*(newtab + 1) = NULL;
		*newtab = ft_new_structpath(".");
		return (newtab);
	}
	if (!(newtab = (t_path **)malloc(sizeof(*newtab) * (ft_tablen(arg) + 1))))
		return (NULL);
	*(newtab + ft_tablen(arg)) = NULL;
	i = 0;
	while (arg[i])
	{
		newtab[i] = ft_new_structpath(arg[i]);
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
		if ((*argpath)->display == NULL)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd((*argpath)->name, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		argpath++;
	}
}

void	ft_printtab_structpath(t_path **tab)
{
	int		i;
	t_list	*current;

	if (!tab)
		return ;
	while (*tab)
	{
		printf("name = %s\n", (*tab)->name);
		printf("display = %s\n", (*tab)->display);
		printf("used = %d\n", (*tab)->used);
		printf("lst_in :\n");
		current = (*tab)->lst_in;
		while (current)
		{
			printf("%s\n", current->content);
			current = current->next;
		}
		printf("insides->name :\n");
		i = 0;
		if ((*tab)->inside)
		{
			while (((*tab)->inside)[i])
			{
				printf("%s\n", (((*tab)->inside)[i])->name);
				i++;
			}
		}
		printf("\n");
		tab++;
	}
}

int		main(int ac, char **av)
{
	char	opt[128];
	t_path	**argpath;

	if (ft_fill_opt(opt, ac, av) == -1)
		exit(EXIT_FAILURE);
	argpath = ft_create_argpath(ft_tab_path(ac, av));
	ft_print_fileerror(argpath);
	ft_putendl("");
	ft_printtab_structpath(argpath);
	ft_del_pathtab(&argpath);
	return (0);
}
