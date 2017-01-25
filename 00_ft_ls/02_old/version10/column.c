/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 11:01:39 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/21 20:20:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

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

void	ft_put_incolumn(t_path **tab, t_padd_col *padd_col, int len_max)
{
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	while (k < padd_col->row)
	{
		i = 0;
		while (i + k < padd_col->file)
		{
			if (tab[i + k]->display)
			{
				len = ft_strlen(tab[i + k]->display);
				ft_print_color(tab[i + k]->display, tab[i + k]);
				while (len % len_max != 0)
				{
					ft_putchar(' ');
					len++;
				}
			}
			i = i + padd_col->row;
		}
		if (k != padd_col->row - 1)
			ft_putendl("");
		k++;
	}
	ft_putendl("");
}

t_padd_col	*ft_get_col(int w_col, int len_max, t_path **tab)
{
	t_padd_col	*padd_col;
	int			tmp_file;

	if (!(padd_col = (t_padd_col *)malloc(sizeof(*padd_col))))
		return (NULL);
	padd_col->col = w_col / len_max;
	padd_col->row = 0;
	padd_col->file = 0;
	if (padd_col->col != 0)
	{
		padd_col->file = ft_pathtablen(tab);
		if (padd_col->file % padd_col->col != 0)
			padd_col->row = padd_col->file / padd_col->col + 1;
		else
			padd_col->row = padd_col->file / padd_col->col;
		if (padd_col->row > 1)
		{
			tmp_file = padd_col->file - ((padd_col->row - 1) * padd_col->col);
			while (tmp_file < padd_col->col - 1)
			{
				tmp_file = tmp_file + (padd_col->row - 1);
				if (tmp_file < padd_col->col)
					(padd_col->col)--;
			}
		}
	}
	return (padd_col);
}

void	ft_print_column(t_path **tab, char *opt)
{
	int				i;
	struct winsize	*w;
	int				len_max;
	t_padd_col		*padd_col;

	if (!(w = (struct winsize *)malloc(sizeof(*w))))
		return ;
	if (ioctl(1, TIOCGWINSZ, w) != 0)
	{
		free(w);
		ft_nocol(0, tab, opt);
		return ;
	}

	i = 0;
	len_max = 0;
	while (tab[i])
	{
		if (tab[i]->display && (len_max < (int)ft_strlen(tab[i]->display)))
			len_max = ft_strlen(tab[i]->display);
		i++;
	}
	padd_col = ft_get_col(w->ws_col, ++len_max, tab);
	free(w);
	if (ft_nocol(padd_col->col, tab, opt) == 1)
	{
		free(padd_col);
		return ;	
	}
	ft_put_incolumn(tab, padd_col, len_max);
	free(padd_col);
}
