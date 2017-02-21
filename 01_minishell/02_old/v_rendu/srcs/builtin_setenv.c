/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:44:53 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/08 17:58:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char		**ft_setenv_newenv(char *newvar, char **env)
{
	char	**newenv;
	int		i;

	if (!(newenv = (char **)malloc(sizeof(*newenv) * (ft_tablen(env) + 2))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		newenv[i] = ft_strdup(env[i]);
		i++;
	}
	newenv[i] = ft_strdup(newvar);
	newenv[i + 1] = NULL;
	return (newenv);
}

void		ft_setenv_1arg(char **arg, char ***env)
{
	int		varname_len;
	char	*varname;
	char	**tmpenv;

	varname_len = 0;
	while (arg[1][varname_len] && arg[1][varname_len] != '=')
		varname_len++;
	varname = ft_strsub(arg[1], 0, varname_len);
	if (ft_strisalnum(varname) == 0)
	{
		ft_putstr_fd("setenv: Variable name (before '=') ", 2);
		ft_putendl_fd("must contain alphanumeric characters.", 2);
	}
	else if (ft_exist(varname, *env) == 1)
		ft_change_envvar1(*env, arg[1]);
	else
	{
		tmpenv = *env;
		*env = ft_setenv_newenv(arg[1], *env);
		ft_tabdel(&tmpenv);
	}
	ft_strdel(&varname);
}

void		ft_setenv_2arg(char **arg, char ***env)
{
	char	**tmpenv;
	char	*tmpvar;

	if (ft_strisalnum(arg[1]) == 0)
	{
		ft_putstr_fd("setenv: Variable name ", 2);
		ft_putendl_fd("must contain alphanumeric characters.", 2);
	}
	else if (ft_exist(arg[1], *env) == 1)
		ft_change_envvar2(*env, arg[1], arg[2]);
	else
	{
		tmpenv = *env;
		if (!arg[2])
			tmpvar = ft_strjoin(arg[1], "=");
		else
			tmpvar = ft_strjoin3(arg[1], "=", arg[2]);
		*env = ft_setenv_newenv(tmpvar, *env);
		ft_strdel(&tmpvar);
		ft_tabdel(&tmpenv);
	}
}

void		ft_setenv(char **arg, char ***env)
{
	int		nb_arg;

	nb_arg = ft_tablen(arg);
	if (nb_arg == 1)
		ft_puttab(*env);
	else if (nb_arg > 3)
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (ft_isalpha(arg[1][0]) == 0)
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else
	{
		if (ft_strchr(arg[1], '='))
			ft_setenv_1arg(arg, env);
		else
			ft_setenv_2arg(arg, env);
	}
}
