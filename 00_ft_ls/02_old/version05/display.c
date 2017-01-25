/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:56:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/11 18:24:49 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_print_notdir :
** Affiche les fichiers arguments qui ne sont pas des dossiers
*/

void	ft_print_notdir(t_path **argpath)
{
	int		i;
	int		cpt_dir;
	int		cpt_notdir;

	i = 0;
	cpt_dir = 0;
	cpt_notdir = 0;
	while (argpath[i])
	{
		if (ft_isdir(argpath[i]) == 0 && argpath[i]->display)
		{
			ft_putendl(argpath[i]->display);
			cpt_notdir++;
		}
		if (ft_isdir(argpath[i]) == 1)
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
			ft_putendl(tab->inside[j]->display);
			j++;
		}
	}
}

/*
** ft_print_dirpath :
** Affiche le chemin du dossier avant son contenu
*/

void	ft_print_dirpath(t_path *tab, int len)
{
	if (len != 1 && ft_isdir(tab))
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
	if (tab->error == EACCES && ft_isdir(tab) == 1)
	{
		ft_putstr_fd("ls: ", 2);
		if (ft_strchr(tab->display, '/') != NULL)
			ft_putstr_fd(ft_strrchr(tab->display, '/') + 1, 2);
		else
			ft_putstr_fd(tab->display, 2);
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
		ft_print_notdir(argpath);
		last = 0;
		i = -1;
		while (argpath[++i])
			ft_isdir(argpath[i]) ? last = i : 0;
		i = -1;
		while (argpath[++i])
		{
			ft_run(argpath[i]->inside, opt, f);
			ft_print_dirpath(argpath[i], len);
			ft_print_erracc(argpath[i]);
			ft_print_indir(argpath[i]);
			i != last && ft_isdir(argpath[i]) ? ft_putendl("") : 0;
		}
	}
}
