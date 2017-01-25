/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2016/12/31 16:36:37 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** Ne marche pas, la mainupalition des struct de struct alors que j'en suis
** qu'au debut, ca devient compliqué et ca ne fait pas ce que je veux. Abandon.
*/

/*
** ft_tab_arg :
** Retourne l'adresse du pointeur du premier arg fichier (pas option)  de ft_ls
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

/*char	**ft_fill_argfiles(char **arg)
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
}*/

t_list	*ft_fill_argfiles(char **arg)
{
	t_list			*argfiles;
	
	argfiles = NULL;
	while (*arg)
	{
		ft_lstadd_back(&argfiles, ft_lstnew(ft_new_filestat(*arg), 0));
		arg++;
	}
	return (argfiles);
}

void	ft_printlst(t_list *lst)
{
	while (lst)
	{
		if (!(lst->content))
			printf("NULL\n");
		else
			printf("OK\n");
		lst = lst->next;
	}
}

int		main(int ac, char **av)
{
	char	opt[128];
	t_list	*argfiles;

	if (ft_fill_opt(opt, ac, av) == -1)
		exit(EXIT_FAILURE);
	argfiles = ft_fill_argfiles(ft_tab_arg(ac, av));
	ft_printlst(argfiles);
	printf("name first file = %s\n", ((t_filestat *)(argfiles->content))->name);
	return (0);
}
