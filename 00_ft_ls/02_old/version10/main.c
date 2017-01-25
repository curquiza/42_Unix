/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/21 16:44:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		main(int ac, char **av)
{
	char	opt[128];
	t_path	**argpath;
	void	(*f[4])(t_path **, char *);

	ft_start(ac, av, &argpath, opt);
	ft_init_fcttab(f);
	ft_display(argpath, opt, f);
	//while (1){}
	return (0);
}
