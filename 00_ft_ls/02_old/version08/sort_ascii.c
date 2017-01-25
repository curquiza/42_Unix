/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 11:02:29 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/16 12:20:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_run_mergesort et ft_init_tmp:
** Tri et fusionne deux sous tableaux
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
		else if (ft_strcmp(tmp[cpt1 - start1]->name, tab[cpt2]->name) < 0)
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
** ft_sortascii_pathtab:
** Tri par fusion
*/

void			ft_sortascii_pathtab(t_path **tab)
{
	int		len;

	len = ft_pathtablen(tab);
	if (len > 0)
		ft_merge_sort(tab, 0, len - 1);
}
