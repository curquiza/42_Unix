/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:49:23 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/16 12:10:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*void	ft_sorttime_pathtab(t_path **tab)
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
}*/

/*
** ft_run_mergesort, ft_init_tmp et ft_timecmp :
** Tri par temps de modif et fusionne deux sous tableaux
*/

static t_path	**ft_init_tmp(t_path **tab, int start1, int end1)
{
	int		i;
	t_path	**tmp;

	if (!(tmp = (t_path **)malloc(sizeof(*tmp) * (end1 - start1 + 1))))
		return (NULL);
	i = start1;
	while (i <= end1)
	{
		tmp[i - start1] = tab[i];
		i++;
	}
	return (tmp);
}

static int		ft_timecmp(t_path *tab1, t_path *tab2)
{
	if (tab1->lstat.st_mtimespec.tv_sec > tab2->lstat.st_mtimespec.tv_sec)
		return (1);
	if ((tab1->lstat.st_mtimespec.tv_sec == tab2->lstat.st_mtimespec.tv_sec)
		&& (tab1->lstat.st_mtimespec.tv_nsec
			>= tab2->lstat.st_mtimespec.tv_nsec))
		return (1);
	return (0);
}

static void		ft_run_mergesort(t_path **tab, int start1, int end1, int end2)
{
	t_path	**tmp;
	int		start2;
	int		cpt1;
	int		cpt2;
	int		i;

	start2 = end1 + 1;
	cpt1 = start1;
	cpt2 = start2;
	if ((tmp = ft_init_tmp(tab, start1, end1)) == NULL)
		return ;
	i = start1;
	while (i <= end2)
	{
		if (cpt1 == start2)
			break ;
		else if (cpt2 == end2 + 1)
			tab[i] = tmp[cpt1++ - start1];
		else if (ft_timecmp(tmp[cpt1 - start1], tab[cpt2]) == 1)
			tab[i] = tmp[cpt1++ - start1];
		else
			tab[i] = tab[cpt2++];
		i++;
	}
	free(tmp);
}

/*
** ft_merge_sort :
** Sépare le tableau en sous tableau et lance le tri-fusion par sous tableaux
*/

static void		ft_merge_sort(t_path **tab, int start, int end)
{
	int		middle;

	middle = (end + start) / 2;
	if (start != end)
	{
		ft_merge_sort(tab, start, middle);
		ft_merge_sort(tab, middle + 1, end);
		ft_run_mergesort(tab, start, middle, end);
	}
}

void	ft_opt_t(t_path **tab, char *opt)
{
	int		len;
	if (opt['t'] == 0)
		return ;
	len = ft_pathtablen(tab);
	if (len > 0)
		ft_merge_sort(tab, 0, len - 1);
}
