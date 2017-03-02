/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bigT.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 20:05:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 20:54:35 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void			ft_date_bigt(t_path *tab, t_max_optl *max)
{
	int		i;
	int		j;
	char	*tmp_date;

	i = 18 + max->link + max->uid + max->gp + max->size_majmin;
	tmp_date = ctime(&tab->lstat.st_mtimespec.tv_sec);
	j = 4;
	while (tmp_date[j] != '\n')
	{
		tab->display[i] = tmp_date[j];
		i++;
		j++;
	}
}

void			ft_opt_bigt(t_path **tab, char *opt)
{
	t_max_optl		*max;
	int				i;
	char			*tmp_display;

	if (opt['T'] == 0)
		return ;
	if (opt['T'] == 1 && opt['l'] == 0)
		return ;
	if ((max = ft_get_max(tab)) == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i]->display)
		{
			tmp_display = tab[i]->display;
			if (!(tab[i]->display = ft_malloc_display(tab[i], max, 39)))
				return ;
			ft_fill_display(tab[i], max, tmp_display, opt);
		}
		i++;
	}
	free(max);
}
