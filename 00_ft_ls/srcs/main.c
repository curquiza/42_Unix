/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 21:34:24 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		main(int ac, char **av)
{
	char	opt[128];
	t_path	**argpath;
	void	(*f[10])(t_path **, char *);

	ft_start(ac, av, &argpath, opt);
	ft_init_fcttab(f);
	ft_run(argpath, opt, f);
	ft_display(argpath, opt, f);
	return (0);
}
