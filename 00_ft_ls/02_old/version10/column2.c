/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 11:01:39 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/21 18:53:01 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*void	ft_print_column(t_path **tab, char *opt)
{
	int		i;
	struct winsize	*w;

	w = (struct winsize *)malloc(sizeof(*w));
	ft_putnbr_endl(ioctl(0, TIOCGWINSZ, w));
	ft_putnbr_endl(w->ws_col);
	i = 0;
	while (tab[i])
	{
		if (tab[i]->display)
			ft_print(tab[i], opt);
		i++;
	}
	free(w);
}*/

int		ft_nocol(int col, t_path **tab, char *opt)
{
	int		i;

	i= 0;
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

void	ft_put_incolumn(t_path **tab, int nb_col, int len_max)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		nb_file;
	int		nb_row;

	i = 0;
	j = 0;
	nb_file = ft_pathtablen(tab);
	if (nb_file % nb_col != 0)
		nb_row = nb_file / nb_col + 1;
	else
		nb_row = nb_file / nb_col;
	printf("nb_row 2 = %d\n", nb_row);
	k = 0;
	while (k < nb_row)
	{
		i = 0;
		while (tab[i + k])
		{
			if (tab[i + k]->display)
			{
				len = ft_strlen(tab[i + k]->display);
				if (j == nb_col)
				{
					ft_putendl("");
					j = 0;
				}
				ft_print_color(tab[i + k]->display, tab[i + k]);
				j++;
				while (len % len_max != 0)
				{
					ft_putchar(' ');
					len++;
				}
			}
			i = i + nb_row;
			if (i > nb_file)
				break ;
		}
		k++;
	}
	ft_putendl("");
}

/*void	ft_put_incolumn(t_path **tab, int nb_col, int len_max)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i]->display)
		{
			len = ft_strlen(tab[i]->display);
			if (j == nb_col)
			{
				ft_putendl("");
				j = 0;
			}
			ft_print_color(tab[i]->display, tab[i]);
			j++;
			while (len % len_max != 0)
			{
				ft_putchar(' ');
				len++;
			}
		}
		i++;
	}
	ft_putendl("");
}*/

int		ft_get_ncol(int w_col, int len_max, t_path **tab)
{
	int		nb_row;
	int		nb_file;
	int		nb_col;
	int		tmp_file;

	nb_col = w_col / len_max;
	if (nb_col == 0)
		return (0);
	nb_file = ft_pathtablen(tab);
	if (nb_file % nb_col != 0)
		nb_row = nb_file / nb_col + 1;
	else
		nb_row = nb_file / nb_col;
	printf("nb_row = %d\n", nb_row);
	if (nb_row > 1)
	{
		tmp_file = nb_file - ((nb_row - 1) * nb_col);
		printf("nb_col = %d\n", nb_col);
		printf("nb_file = %d\n", nb_file);
		/*if ((tmp_file % 2 == 0 && nb_col % 2 == 1)
			|| (tmp_file % 2 == 1 && nb_col % 2 == 0))
			tmp_file++;*/
		//while (tmp_file + 1 != nb_col)
		while (tmp_file <  nb_col - 1)
		{
			nb_col--;
			tmp_file++;
		}
	}
	printf("nb_col APRES = %d\n", nb_col);
	return (nb_col);
}

void	ft_print_column(t_path **tab, char *opt)
{
	int				i;
	struct winsize	*w;
	int				len_max;
	int				ncol;

	if (!(w = (struct winsize *)malloc(sizeof(*w))))
		return ;
	ioctl(1, TIOCGWINSZ, w);
	i = 0;
	len_max = 0;
	while (tab[i])
	{
		if (tab[i]->display && (len_max < (int)ft_strlen(tab[i]->display)))
			len_max = ft_strlen(tab[i]->display);
		i++;
	}
	ncol = ft_get_ncol(w->ws_col, ++len_max, tab);
	free(w);
	if (ft_nocol(ncol, tab, opt) == 1)
		return ;	
	ft_put_incolumn(tab, ncol, len_max);
}
