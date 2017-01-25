/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:49:23 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/08 15:10:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void	ft_sorttime_pathtab(t_path **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i + 1])
		{
			if (tab[i]->lstat.st_mtimespec.tv_sec
				< tab[i + 1]->lstat.st_mtimespec.tv_sec)
			{
				ft_swap_pathtab(tab, i, i + 1);
				i = -1;
			}
			else if ((tab[i]->lstat.st_mtimespec.tv_sec
						== tab[i + 1]->lstat.st_mtimespec.tv_sec)
					&& (tab[i]->lstat.st_mtimespec.tv_nsec
						< tab[i + 1]->lstat.st_mtimespec.tv_nsec))
			{
				ft_swap_pathtab(tab, i, i + 1);
				i = -1;
			}
			i++;
		}
	}
}

void	ft_opt_t(t_path **tab, char *opt)
{
	if (opt['t'] == 1)
		ft_sorttime_pathtab(tab);
}
