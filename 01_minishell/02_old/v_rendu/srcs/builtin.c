/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:37:38 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/10 15:38:20 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_exit_if(char *bin, t_command **com)
{
	if (ft_strcmp(bin, "exit") == 0)
	{
		ft_comdel(&com);
		exit(1);
	}
}

int		ft_callbuiltin_if(t_command *com, char ***env)
{
	ft_strcmp(com->bin, "echo") == 0 ? ft_echo(com->arg) : 0;
	ft_strcmp(com->bin, "cd") == 0 ? ft_cd(com->arg, env) : 0;
	ft_strcmp(com->bin, "env") == 0 ? ft_env(com->arg, *env) : 0;
	ft_strcmp(com->bin, "setenv") == 0 ? ft_setenv(com->arg, env) : 0;
	ft_strcmp(com->bin, "unsetenv") == 0 ? ft_unsetenv(com->arg, env) : 0;
	if (!ft_strcmp(com->bin, "echo") || !ft_strcmp(com->bin, "cd")
		|| !ft_strcmp(com->bin, "env") || !ft_strcmp(com->bin, "setenv")
		|| !ft_strcmp(com->bin, "unsetenv"))
		return (1);
	return (0);
}
