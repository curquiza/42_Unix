/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:27:12 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/10 14:53:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_init_shlvl(char ***env)
{
	char	*str_value;
	int		int_value;

	if (ft_exist("SHLVL", *env) == 0)
		int_value = 0;
	else
	{
		str_value = ft_get_envvar("SHLVL", *env) + 6;
		int_value = ft_atoi(str_value);
	}
	int_value++;
	str_value = ft_itoa(int_value);
	ft_change_env2(env, "SHLVL", str_value);
	ft_strdel(&str_value);
}

void	ft_initenv(char ***env, char **environ)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	*env = ft_tabdup(environ);
	ft_init_shlvl(env);
	ft_change_env2(env, "PWD", pwd);
	ft_strdel(&pwd);
}
