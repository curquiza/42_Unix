/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:56:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/20 10:36:35 by curquiza         ###   ########.fr       */
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

int		ft_isnotsrch(t_path *tab, char *opt, int is_start)
{
	int		i;

	if (ft_toopen(tab, opt, is_start) == 0)
		return (0);
	if (!tab->inside)
		return (0);
	i = 0;
	while (tab->inside[i])
	{
		if (tab->inside[i]->display == NULL && tab->inside[i]->error == 13)
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_innotsrch(t_path *tab, char *opt)
{
	int		i;
	
	if (!tab->inside)
		return ;
	i = 0;
	while (tab->inside[i])
	{
		ft_print_err(tab->inside[i]);
		i++;
	}
	if (opt['R'] == 1)
	{
		ft_putstr_fd("ls: ", 2);
		if (ft_strchr(tab->name, '/') != NULL)
			ft_putstr_fd(ft_strrchr(tab->name, '/') + 1, 2);
		else
			ft_putstr_fd(tab->name, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}

void	ft_print_indir(t_path *tab, char *opt, int is_start)
{
	int		j;

	if (ft_isnotsrch(tab, opt, is_start) == 1)
	{
		ft_print_innotsrch(tab, opt);
		return ;
	}
	if (opt['l'] == 1)
		ft_print_total(tab->inside);
	ft_print_err(tab);
	if (tab->inside)
	{
		j = 0;
		while (tab->inside[j])
		{
			if (tab->inside[j]->display != NULL)
				ft_putendl(tab->inside[j]->display);
			j++;
		}
	}
}

/*
** ft_print_err :
** Affiche le message d'erreur "Permission denied" à la place du contenu du
** dossier
*/

void	ft_print_err(t_path *tab)
{
	if (tab->error != 0 && tab->error != 20 && tab->error != 2)
	{
		ft_putstr_fd("ls: ", 2);
		if (ft_strchr(tab->name, '/') != NULL)
			ft_putstr_fd(ft_strrchr(tab->name, '/') + 1, 2);
		else
			ft_putstr_fd(tab->name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(tab->error), 2);
	}
	/*if (tab->error == EACCES)
	{
		ft_putstr_fd("ls: ", 2);
		if (ft_strchr(tab->name, '/') != NULL)
			ft_putstr_fd(ft_strrchr(tab->name, '/') + 1, 2);
		else
			ft_putstr_fd(tab->name, 2);
		ft_putendl_fd(": Permission denied", 2);
	}*/
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
			if (opt['l'] == 1 && S_ISLNK(argpath[i]->lstat.st_mode))
				continue ;
			ft_run(argpath[i]->inside, opt, f);
			ft_print_dirpath(argpath[i], len);
			ft_print_indir(argpath[i], opt, 1);
			i != last && ft_toopen(argpath[i], opt, 1) ? ft_putendl("") : 0;
		}
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
		ft_putstr(tab->name);
		ft_putendl(":");
	}
}

