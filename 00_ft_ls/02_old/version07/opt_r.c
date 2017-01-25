/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 14:57:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/06 16:04:54 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void	ft_reverse_pathtab(t_path **tab)
{
	int		i;
	int		len;

	len = ft_pathtablen(tab) - 1;
	i = 0;
	if (tab)
	{
		while (i <= len / 2)
		{
			ft_swap_pathtab(tab, i, len - i);
			i++;
		}
	}
}

void	ft_opt_r(t_path **tab, char *opt)
{
	if (opt['r'] == 1)
		ft_reverse_pathtab(tab);
}
