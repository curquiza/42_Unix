/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bigl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 20:48:34 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 11:40:19 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_opt_bigl :
** Activation de l'option L = les liens softs sont maintenant traités comme les
** files sur lesquels ils pointent (dans l'affichage de l, pour les couleurs...)
**
** /!\ Les xattr sont ceux du lien et non du file sur lequel il pointe
**
** En chantier, pose problème sur /Users/curquiza/Library/Containers/com.apple.iCal.CalendarNC/Data/Library/Preferences/ByHost
*/

static t_path	**ft_get_tmp(t_path **argpath, int size)
{
	int		i;
	int		j;
	t_path	**tmp;

	if (!(tmp = (t_path **)malloc(sizeof(*tmp) * (size + 1))))
		return (NULL);
	tmp[size] = NULL;
	i = 0;
	j = 0;
	while (argpath[i])
	{
		if (argpath[i]->error != -1)
		{
			tmp[j] = argpath[i];
			argpath[i] = NULL;
			j++;
		}
		i++;
	}
	i = -1;
	while (tmp[++i])
		argpath[i] = tmp[i];
	return (tmp);
}

void			ft_opt_bigl(t_path **argpath, char *opt)
{
	int		i;
	int		cpt;
	int		len;
	t_path	**tmp;

	if (opt['L'] == 0)
		return ;
	cpt = 0;
	i = 0;
	while (argpath[i])
	{
		if (S_ISLNK(argpath[i]->lstat.st_mode) && argpath[i]->stat.st_ino == 0)
		{
			ft_putstr("argpath[i] = ");
			ft_putendl(argpath[i]->display);
			argpath[i]->error = -1;
			cpt++;
		}
		else if (S_ISLNK(argpath[i]->lstat.st_mode))
			argpath[i]->lstat = argpath[i]->stat;
		i++;
	}
	ft_putstr("cpt = ");
	ft_putnbr_endl(cpt);
	len = ft_pathtablen(argpath);
	if (!(tmp = ft_get_tmp(argpath, len - cpt)))
		return ;
	free(tmp);
}
