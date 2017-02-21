/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:52:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/05 14:41:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_init_shlvl(char **env)
{
	char	*str_value;
	int		int_value;

	while (*env && ft_strncmp(*env, "SHLVL=", 6) != 0)
		env++;
	str_value = (*env) + 6;
	int_value = ft_atoi(str_value);
	int_value++;
	str_value = ft_itoa(int_value);
	ft_change_envvar1(env, "SHLVL", str_value);
	ft_strdel(&str_value);
}

char	**ft_get_path(char **env)
{
	char 	*line;

	line = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			line = *env;
			break ;
		}
		env++;
	}
	return (ft_strsplit(line + 5, ':'));
}

void	ft_change_envvar1(char **env, char *varname, char *newvalue)
{
	char	*tmpvar;
	//char	*supp;

	tmpvar = ft_strjoin(varname, "=");
	while (*env && ft_strncmp(*env, tmpvar, ft_strlen(tmpvar)) != 0)
		env++;
	ft_strdel(&(*env));
	//supp = *env;
	*env = ft_strjoin(tmpvar, newvalue);
	//ft_strdel(&supp);
	ft_strdel(&tmpvar);
}


void	ft_change_envvar2(char **env, char *newvar)
{
	//char	*supp;
	int		len;

	len = 0;
	while (newvar[len] && newvar[len] != '=')
		len++;
	while (*env && ft_strncmp(*env, newvar, len + 1) != 0)
		env++;
	ft_strdeldup(&(*env), newvar);
	//supp = *env;
	//*env = ft_strdup(newvar);
	//ft_strdel(&supp);
}
