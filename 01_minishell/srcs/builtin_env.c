/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:19:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/05 15:19:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_env(char **arg, char **env)
{
	int		nb_arg;

	nb_arg = ft_tablen(arg);
	if (nb_arg == 1)
		ft_puttab(env);
}
