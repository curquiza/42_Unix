/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcttab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:54:02 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/06 17:29:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_init_fcttab :
** Initialise le tableau de fonctions avec les fonctions de chaque option sauf :
** - a car déjà appliquée dans ft_get_lst_in
** - R car appliqué plus tard en tant qu'affichage particulier
*/

void	ft_init_fcttab(void (**f)(t_path **, char *))
{
	f[0] = &ft_opt_t;
	f[1] = &ft_opt_r;
	f[2] = NULL;
}

/*
** ft_run :
** Applique les fonctions associée à chaque option dans l'ordre du tableau.
*/

void	ft_run(t_path **argpath, char *opt, void (**f)(t_path **, char *))
{
	int		i;

	i = 0;
	while (f[i])
	{
		(f[i])(argpath, opt);
		i++;
	}
}
