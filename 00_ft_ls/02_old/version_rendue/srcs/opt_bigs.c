/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bigs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:25:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 19:15:37 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_run_mergesort et ft_init_tmp:
** Trient et fusionnent deux sous tableaux
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
		else if (tmp[cpt1 - start1]->lstat.st_size > tab[cpt2]->lstat.st_size)
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

/*
** ft_opt_bigs :
** Activation de l'opt S = Tri (ici, par fusion) par size. Ordre décroissant.
** Annule l'opt t;
*/

void			ft_opt_bigs(t_path **argpath, char *opt)
{
	int		len;

	if (opt['S'] == 0)
		return ;
	opt['t'] = 0;
	len = ft_pathtablen(argpath);
	if (len > 0)
		ft_merge_sort(argpath, 0, len - 1);
}
