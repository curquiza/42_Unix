/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:56:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/19 17:21:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_print_notdir :
** Affiche les fichiers arguments qui ne sont pas des dossiers
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
** ft_print_indir :
** Affiche le contenu du dossier
*/

void	ft_print_indir(t_path *tab)
{
	int		j;

	if (tab->inside)
	{
		j = 0;
		while (tab->inside[j])
		{
			//if (tab->inside[j]->display)
			//	ft_putendl(tab->inside[j]->display);
			//else
			//	ft_putendl(ft_strrchr(tab->inside[j]->name, '/') + 1);
			if (tab->inside[j]->display != NULL)
				ft_putendl(tab->inside[j]->display);
			j++;
		}
	}
}

/*void	ft_print_indir(t_path *tab, char *opt)
{
	int		j;

	if (tab->inside)
	{
		if (opt['l'] == 1)
		{
			j = 0;
			while (tab->inside[j])
			{
				ft_putstr_fd("ls: ", 2);
				if (tab->inside[j]->display)
					ft_putstr_fd(tab->inside[j]->display, 2);
				else
					ft_putstr_fd(ft_strrchr(tab->inside[j]->name, '/') + 1, 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(tab->inside[j]->error), 2);
				j++;
			}
		}
		j = 0;
		while (tab->inside[j])
		{
			if (tab->inside[j]->display != NULL)
				ft_putendl(tab->inside[j]->display);
			j++;
		}
	}
}*/

/*
** ft_print_dirpath :
** Affiche le chemin du dossier avant son contenu
*/

void	ft_print_dirpath(t_path *tab, int len)
{
	if (len != 1 && tab->display && (tab->error == 0 || tab->error == 13))
	{
		ft_putstr(tab->name);
		ft_putendl(":");
	}
}

/*
** ft_print_accerr :
** Affiche le message d'erreur "Permission denied" à la place du contenu du
** dossier
*/

void	ft_print_erracc(t_path *tab)
{
/*	if (tab->error == EACCES && tab->display != NULL)
	{
		ft_putstr_fd("ls: ", 2);
		if (ft_strchr(tab->display, '/') != NULL)
			ft_putstr_fd(ft_strrchr(tab->display, '/') + 1, 2);
		else
			ft_putstr_fd(tab->display, 2);
		ft_putendl_fd(": Permission denied", 2);
	}*/
	if (tab->error == EACCES/* && tab->display != NULL*/)
	{
		ft_putstr_fd("ls: ", 2);
		if (ft_strchr(tab->name, '/') != NULL)
			ft_putstr_fd(ft_strrchr(tab->name, '/') + 1, 2);
		else
			ft_putstr_fd(tab->name, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}

/*
** ft_classic_display :
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
		last = 0;
		i = -1;
		while (argpath[++i])
			ft_toopen(argpath[i], opt, 1) ? last = i : 0;
		i = -1;
		while (argpath[++i])
		{
			ft_run(argpath[i]->inside, opt, f);
			if (opt['l'] == 1 && S_ISLNK(argpath[i]->lstat.st_mode))
				continue ;
			ft_print_dirpath(argpath[i], len);
			if (opt['l'] == 1)
				ft_print_total(argpath[i]->inside);
			ft_print_erracc(argpath[i]);
			ft_print_indir(argpath[i]);
			i != last && ft_toopen(argpath[i], opt, 1) ? ft_putendl("") : 0;
		}
	}
}
