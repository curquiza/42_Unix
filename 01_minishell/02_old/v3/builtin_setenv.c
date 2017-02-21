/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:44:53 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/05 15:14:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** ft_exist :
** Returns 1 if the variable already exists, otherwise returns 0.
*/

int			ft_exist(char *varname, char **env)
{
	int		len;

	len = ft_strlen(varname);
	while (*env)
	{
		if (ft_strncmp(*env, varname, len) == 0)
			return (1);
		env++;
	}
	return (0);
}

void		ft_setenv(char **arg, char ***env)
{
	int		nb_arg;
	int		varname_len;
	char	*varname;
	char	**tmpenv;
	int		i;

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
		{
			varname_len = 0;
			while (arg[1][varname_len] && arg[1][varname_len] != '=')
				varname_len++;
			varname = ft_strsub(arg[1], 0, varname_len);
			if (ft_strisalnum(varname) == 0)
			{
				ft_putendl_fd("setenv: Variable name (before '=') must contain alphanumeric characters.", 2);
				exit(1);
			}
			if (ft_exist(varname, *env) == 1)
				ft_change_envvar2(*env, arg[1]);
			else
			{
				tmpenv = *env;
				if (!(*env = (char **)malloc(sizeof(**env) * (ft_tablen(tmpenv) + 2))))
					return ;
				i = 0;
				while (tmpenv[i])
				{
					(*env)[i] = ft_strdup(tmpenv[i]);
					i++;
				}
				(*env)[i] = ft_strdup(arg[1]);
				(*env)[i + 1] = NULL;
				ft_tabdel(&tmpenv);
			}
			//ft_puttab(*env);
		}


	}
	//exit(0);
}
