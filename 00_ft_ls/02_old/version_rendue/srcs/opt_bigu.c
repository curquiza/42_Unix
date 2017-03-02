/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bigu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:30:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 19:01:56 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_opt_bigu :
** Activation de l'opt U = prise en compte du temps de creation à la place
** du temps de modif pour le long format (opt l) et le tri par tmps (opt t)
*/

void	ft_opt_bigu(t_path **argpath, char *opt)
{
	int		i;

	if (opt['U'] == 0)
		return ;
	i = 0;
	while (argpath[i])
	{
		argpath[i]->lstat.st_mtimespec = argpath[i]->lstat.st_birthtimespec;
		argpath[i]->stat.st_mtimespec = argpath[i]->stat.st_birthtimespec;
		i++;
	}
}
