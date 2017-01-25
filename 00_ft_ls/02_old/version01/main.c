/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2016/12/31 13:30:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_tab_arg :
** Retourne l'adresse du pointeur du premier arg de ft_ls
** Peut renvoyer NULL <=> le seul argument de ls sera alors "."
*/

char	**ft_tab_arg(int ac, char **av)
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

int		ft_nb_errors(char **arg)
{
	int				cpt;
	struct stat		test;

	if (!arg)
		return (0);
	cpt = 0;
	while (*arg)
	{
		if (lstat(*arg, &test) < 0)
			cpt++;
		arg++;
	}
	return (cpt);
}

/*
** ft_print_fileerror :
** Trie le tableau error par ordre ascii et l'affiche avec les message d'erreur
** Puis free le tabeau.
*/

void	ft_print_fileerror(char **tab)
{
	if (!tab)
		return ;
	ft_sorttab_ascii(tab);
	while (*tab)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(*tab, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		tab++;
	}
	free(tab);
}

/*
** ft_fill_argfiles :
** Affiche les fichiers non existants (avec message d'erreur)
** et retourne un char ** correspondant au tableau des noms de files valides
*/

char	**ft_fill_argfiles(char **arg)
{
	char			**error;
	char			**files;
	struct stat		test;
	int				i;
	int				j;

	if (!arg)
		return (NULL);
	if (!(error = (char **)malloc(sizeof(*error) * (ft_nb_errors(arg) + 1))) ||
		!(files = (char **)malloc(sizeof(*files) *
									(ft_tablen(arg) - ft_nb_errors(arg) + 1))))
		return (NULL);
	error[ft_nb_errors(arg)] = NULL;
	files[ft_tablen(arg) - ft_nb_errors(arg)] = NULL;
	i = 0;
	j = 0;
	while (*arg)
	{
		if (lstat(*arg, &test) < 0)
			error[i++] = *(arg++);
		else
			files[j++] = *(arg++);
	}
	ft_print_fileerror(error);
	return (files);
}

int		main(int ac, char **av)
{
	char	opt[128];
	char	**arg_files;

	if (ft_fill_opt(opt, ac, av) == -1)
		exit(EXIT_FAILURE);
	arg_files = ft_fill_argfiles(ft_tab_arg(ac, av));
	ft_puttab(arg_files);
	return (0);
}
