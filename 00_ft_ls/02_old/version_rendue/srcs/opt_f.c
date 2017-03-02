/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 21:09:12 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/22 21:15:48 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_opt_f :
** Activation de l'option f = abscence de tri + active l'opt a
*/

void	ft_opt_f(t_path **argpath, char *opt)
{
	(void)argpath;
	if (opt['f'] == 0)
		return ;
	opt['a'] = 1;
	opt['r'] = 0;
	opt['t'] = 0;
	opt['S'] = 0;
}
