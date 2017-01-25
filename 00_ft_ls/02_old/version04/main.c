/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/08 14:54:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"



void	ft_print_pathtab(t_path **tab)
{
	int		i;
	t_list	*current;

	if (!tab)
		return ;
	while (*tab)
	{
		printf("name = %s\n", (*tab)->name);
		printf("display = %s\n", (*tab)->display);
		//printf("permerror = %d\n", (*tab)->permerror);
		printf("error = %d\n", (*tab)->error);
		printf("date modif lstat : %s", ctime(&(*tab)->lstat.st_mtimespec.tv_sec));
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

/*
** ft_print_notdir :
** Affiche les fichiers arg "non ouvrables" (autres que les options)
**
** FAUX : si le dossier est vide !!
*/

void	ft_print_notdir(t_path **argpath, int len)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (argpath[i])
	{
		if (ft_isdir(argpath[i]) == 0 && argpath[i]->display != NULL)
		{
			ft_putendl(argpath[i]->display);
			cpt++;
		}
		i++;
	}
	if (cpt != len && cpt != 0)
		ft_putendl("");
}

/*
** EN COURS
*/

void	ft_classic_display(t_path **argpath, char *opt,
												void (**f)(t_path **, char *))
{
	int		i;
	int		j;
	int		len;

	if (opt['R'] == 1)
		return ;
	len = ft_pathtablen(argpath);
	ft_run(argpath, opt, f);
	ft_print_notdir(argpath, len);
	i = 0;
	while (argpath[i])
	{
		if (len != 1 && ft_isdir(argpath[i]))
		{
			ft_putstr(argpath[i]->name);
			ft_putendl(":");
			ft_run(argpath[i]->inside, opt, f);
		}
		if (argpath[i]->error == 13/)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(ft_strrchr(argpath[i]->display, '/') + 1, 2);
			ft_putendl_fd(": Permission denied", 2);
		}
		if (ft_isdir(argpath[i]))
		{
			if (argpath[i]->inside)
			{
				ft_run(argpath[i]->inside, opt, f);
				j = 0;
				while (argpath[i]->inside[j])
				{
					ft_putendl(argpath[i]->inside[j]->display);
					j++;
				}
			}
			if (i != len - 1)
				ft_putendl("");
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	char	opt[128];
	t_path	**argpath;
	void	(*f[3])(t_path **, char *);

	ft_start(ac, av, &argpath, opt);

	ft_init_fcttab(f);
	ft_classic_display(argpath, opt, f);

	ft_putendl("------------------------");
	ft_putendl("------------------------");
	ft_putendl("------------------------");
	ft_print_pathtab(argpath);
	return (0);
}
