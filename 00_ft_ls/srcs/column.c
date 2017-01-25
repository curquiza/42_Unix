/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 11:01:39 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/24 11:50:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_nocol :
** affiche avec des \n entre chaque nom dans le cas ou le nombre de col est nul
*/

int		ft_nocol(int col, t_path **tab, char *opt)
{
	int		i;

	i = 0;
	if (col > 0)
		return (0);
	while (tab[i])
	{
		if (tab[i]->display)
			ft_print_onefile(tab[i], opt);
		i++;
	}
	return (1);
}

/*
** ft_put_incolumn :
** Affichage en colonne
*/

void	ft_put_incolumn(t_path **tab, int row, int len_max, char *opt)
{
	int		i;
	int		k;
	int		len;
	int		file;

	file = ft_pathtablen(tab);
	k = -1;
	while (++k < row)
	{
		i = 0;
		while (i + k < file)
		{
			if (tab[i + k]->display)
			{
				len = ft_strlen(tab[i + k]->display);
				opt['G'] ? ft_print_color(tab[i + k]->display, tab[i + k])
							: ft_putstr(tab[i + k]->display);
				while (len++ % len_max != 0)
					ft_putchar(' ');
			}
			i = i + row;
		}
		k != row - 1 ? ft_putendl("") : 0;
	}
	ft_putendl("");
}

/*
** ft_get_row :
** Retourne le nomnbre de lignes nécessaire
*/

int		ft_get_row(int col, t_path **tab)
{
	int		file;
	int		row;

	file = ft_pathtablen(tab);
	if (file % col != 0)
		row = file / col + 1;
	else
		row = file / col;
	return (row);
}

/*
** ft_print_column :
** Point de départ de la gestion de l'affichge en colonne
*/

void	ft_print_column(t_path **tab, char *opt)
{
	int				i;
	struct winsize	*w;
	int				len_max;
	int				col;

	if (!(w = (struct winsize *)malloc(sizeof(*w))))
		return ;
	if (ioctl(1, TIOCGWINSZ, w) != 0)
	{
		free(w);
		ft_nocol(0, tab, opt);
		return ;
	}
	len_max = 0;
	i = -1;
	while (tab[++i])
	{
		if (tab[i]->display && (len_max < (int)ft_strlen(tab[i]->display)))
			len_max = ft_strlen(tab[i]->display);
	}
	col = w->ws_col / (++len_max);
	free(w);
	if (ft_nocol(col, tab, opt) == 1)
		return ;
	ft_put_incolumn(tab, ft_get_row(col, tab), len_max, opt);
}
