/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:22:25 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 18:51:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_opt_u :
** Activation de l'opt u = prise en compte du temps d'acces à la place du temps
** de modif pour le long format (opt l) et le tri par tmps (opt t)
*/

void	ft_opt_u(t_path **argpath, char *opt)
{
	int		i;

	if (opt['u'] == 0)
		return ;
	i = 0;
	while (argpath[i])
	{
		argpath[i]->lstat.st_mtimespec = argpath[i]->lstat.st_atimespec;
		argpath[i]->stat.st_mtimespec = argpath[i]->stat.st_atimespec;
		i++;
	}
}
