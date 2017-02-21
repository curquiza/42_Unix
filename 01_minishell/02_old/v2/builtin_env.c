/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:19:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/04 17:24:37 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_env(char **arg, char **env)
{
	(void)arg;
	while (*env)
	{
		ft_putendl(*env);
		env++;
	}
	exit(0);
}
