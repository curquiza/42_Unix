/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:05:36 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/17 21:29:59 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** ft_change_envvar1 and ft_change_envvar2 :
** Gives a new value to a variable.
** 1 : "coco=1" format.
** 2 : "coco 1" format.
*/

void	ft_change_envvar1(char **env, char *newvar)
{
	int		len;

	len = 0;
	while (newvar[len] && newvar[len] != '=')
		len++;
	while (*env && ft_strncmp(*env, newvar, len + 1) != 0)
		env++;
	if (!env)
		return ;
	ft_strdeldup(&(*env), newvar);
}

void	ft_change_envvar2(char **env, char *varname, char *newvalue)
{
	char	*tmpvar;

	tmpvar = ft_strjoin(varname, "=");
	while (*env && ft_strncmp(*env, tmpvar, ft_strlen(tmpvar)) != 0)
		env++;
	if (!env)
	{
		ft_strdel(&tmpvar);
		return ;
	}
	ft_strdel(&(*env));
	*env = ft_strjoin(tmpvar, newvalue);
	ft_strdel(&tmpvar);
}

/*
** ft_change_env1 & ft_change_env2 :
** If the variable exists, change the value.
** Otherwise, add the new variable with its value.
** 1 : "coco=1" format.
** 2 : "coco 1" format.
*/

void	ft_change_env1(char ***env, char *newvar)
{
	int		len;
	char	*tmpvar;
	char	**tmpenv;

	len = 0;
	while (newvar[len] && newvar[len] != '=')
		len++;
	tmpvar = ft_strsub(newvar, 0, len);
	if (ft_exist(tmpvar, *env) == 1)
		ft_change_envvar1(*env, newvar);
	else
	{
		tmpenv = *env;
		*env = ft_setenv_newenv(newvar, tmpenv);
		ft_tabdel(&tmpenv);
	}
	ft_strdel(&tmpvar);
}

void	ft_change_env2(char ***env, char *varname, char *value)
{
	char	*tmpvar;
	char	**tmpenv;

	if (ft_exist(varname, *env) == 1)
		ft_change_envvar2(*env, varname, value);
	else
	{
		tmpenv = *env;
		tmpvar = ft_strjoin3(varname, "=", value);
		*env = ft_setenv_newenv(tmpvar, tmpenv);
		ft_tabdel(&tmpenv);
		ft_strdel(&tmpvar);
	}
}
