/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_notdir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 19:26:36 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/24 12:51:32 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_print_notdir :
** Affiche les fichiers arguments qui ne sont pas des "ouvrables"
*/

void	ft_print_notdir(t_path **argpath, char *opt)
{
	int		i;
	int		cpt_dir;
	int		cpt_notdir;
	t_path	**notdir;

	ft_get_cpt(argpath, opt, &cpt_dir, &cpt_notdir);
	if (!(notdir = ft_get_notdir(argpath, opt, cpt_notdir)))
		return ;
	if (opt['l'] == 0 && opt['1'] == 0)
		ft_print_column(notdir, opt);
	else
	{
		i = 0;
		while (notdir[i])
		{
			if (ft_toopen(notdir[i], opt, 1) == 0 && notdir[i]->display)
				ft_print_onefile(notdir[i], opt);
			i++;
		}
	}
	free(notdir);
	(cpt_dir > 0 && cpt_notdir > 0) ? ft_putendl("") : 0;
}

/*
** ft_get_cpt :
** Incrémente les compteurs cpt_dir et cpt_notdir
*/

void	ft_get_cpt(t_path **tab, char *opt, int *cpt_dir, int *cpt_notdir)
{
	int		i;

	i = 0;
	*cpt_dir = 0;
	*cpt_notdir = 0;
	while (tab[i])
	{
		if (ft_toopen(tab[i], opt, 1) == 0 && tab[i]->display)
			(*cpt_notdir)++;
		if (ft_toopen(tab[i], opt, 1) == 1)
			(*cpt_dir)++;
		i++;
	}
}

/*
** ft_get_notdir :
** Créée un tableau de t_path contenant tous les files non ouvrables
*/

t_path	**ft_get_notdir(t_path **tab, char *opt, int cpt_notdir)
{
	int		i;
	int		j;
	t_path	**notdir;

	if (cpt_notdir < 1)
		return (NULL);
	if (!(notdir = (t_path **)malloc(sizeof(*notdir) * (cpt_notdir + 1))))
		return (NULL);
	notdir[cpt_notdir] = NULL;
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i]->display && ft_toopen(tab[i], opt, 1) == 0)
		{
			notdir[j] = tab[i];
			j++;
		}
		i++;
	}
	return (notdir);
}
