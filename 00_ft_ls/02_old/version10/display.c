/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:56:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/20 20:40:20 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_print_notdir :
** Affiche les fichiers arguments qui ne sont pas des "ouvrables"
*/

void	ft_print_notdir(t_path **argpath, char *opt)
{
	int		i;
	int		cpt_dir;
	int		cpt_notdir;

	i = 0;
	cpt_dir = 0;
	cpt_notdir = 0;
	while (argpath[i])
	{
		if (ft_toopen(argpath[i], opt, 1) == 0 && argpath[i]->display)
		{
			ft_putendl(argpath[i]->display);
			cpt_notdir++;
		}
		if (ft_toopen(argpath[i], opt, 1) == 1)
			cpt_dir++;
		i++;
	}
	if (cpt_dir > 0 && cpt_notdir > 0)
		ft_putendl("");
}

/*
** ft_print_err :
** Affiche le message d'erreur adapté sur la sortie 2
*/

void	ft_print_err(t_path *tab)
{
	if (tab->error != 0 && tab->error != 20 && tab->error != 2)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(ft_name_in_path(tab->name), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(tab->error), 2);
	}
}

/*
** ft_print_dirpath :
** Affiche le chemin du dossier avant son contenu
*/

void	ft_print_dirpath(t_path *tab, int len)
{
	if (len != 1 && tab->display && (tab->error == 0 || tab->error == 13))
	{
		//ft_putstr(tab->name);
		//ft_putendl(":");
		ft_putstr_color(tab->name, YELLOW_BOLD);
		ft_putendl_color(":", YELLOW_BOLD);
	}
}

int		ft_get_last(t_path **tab, char *opt)
{
	int		last;
	int		i;

	last = 0;
	i = -1;
	while (tab[++i])
		ft_toopen(tab[i], opt, 1) ? last = i : 0;
	return (last);
}

/*
** ft_display :
** Affichage en fonction de l'activation de l'option R
*/

void	ft_display(t_path **argpath, char *opt, void (**f)(t_path **, char *))
{
	int		i;
	int		last;
	int		len;

	if (opt['R'] == 1)
		ft_opt_bigr(argpath, opt, f);
	else
	{
		len = ft_pathtablen(argpath);
		ft_run(argpath, opt, f);
		ft_print_notdir(argpath, opt);
		last = ft_get_last(argpath, opt);
		i = -1;
		while (argpath[++i])
		{
			if (opt['l'] == 1 && S_ISLNK(argpath[i]->lstat.st_mode))
				continue ;
			ft_run(argpath[i]->inside, opt, f);
			ft_print_dirpath(argpath[i], len);
			ft_print_indir(argpath[i], opt, 1);
			i != last && ft_toopen(argpath[i], opt, 1) ? ft_putendl("") : 0;
		}
	}
}
