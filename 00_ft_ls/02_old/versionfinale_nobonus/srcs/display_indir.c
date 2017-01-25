/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_indir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:08:09 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/21 12:01:36 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_isnotsrch et ft_print_innotsrch :
** Cas particulier d'un dossier avec droit de lecture mais pas de droit de
** traverse.
** Ex : /Library/Scripts/42/munki
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
		ft_putstr_fd(ft_name_in_path(tab->name), 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}

/*
** ft_print_total :
** Affiche le total dans le cas de l'option l.
*/

void	ft_print_total(t_path **tab)
{
	int		i;
	int		blocks;
	char	*tmp_name;

	if (!tab)
		return ;
	i = 0;
	blocks = 0;
	while (tab[i])
	{
		tmp_name = ft_name_in_path(tab[i]->name);
		if (ft_strcmp(tmp_name, ".") != 0 && ft_strcmp(tmp_name, "..") != 0)
			blocks = blocks + tab[i]->lstat.st_blocks;
		i++;
	}
	ft_putstr("total ");
	ft_putnbr_endl(blocks);
}

/*
** ft_print_indir :
** Affiche le contenu du dossier. Vient après l'affichage du nom du dossier.
*/

void	ft_print_indir(t_path *tab, char *opt, int is_start)
{
	int		j;

	if (ft_isnotsrch(tab, opt, is_start) == 1)
	{
		ft_print_innotsrch(tab, opt);
		return ;
	}
	ft_print_err(tab);
	if (tab->inside)
	{
		if (opt['l'] == 1)
			ft_print_total(tab->inside);
		j = 0;
		while (tab->inside[j])
		{
			if (tab->inside[j]->display != NULL)
				ft_putendl(tab->inside[j]->display);
				//ft_print(tab->inside[j], opt);
			j++;
		}
	}
}

/*
** ft_print :
** Affiche le champ display en tenant compte de la couleur
*/

void	ft_print(t_path *tab, char *opt)
{
	int		len;
	int		i;
	char	*name;

	if (opt['l'] == 1)
	{
		name = ft_name_in_path(tab->name);
		len = ft_strlen(name);
		i = -1;
		while (tab->display[++i])
		{
			if (ft_strncmp(tab->display + i, name, len) == 0)
				break ;
		}
		write(1, tab->display, i);
		ft_print_color(name, tab);
		ft_putendl(tab->display + i + len);
	}
	else
	{
		ft_print_color(tab->display, tab);
		ft_putendl("");
	}
}
