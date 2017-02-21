/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:52:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/10 14:06:44 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** ft_exist :
** Returns 1 if the variable already exists, otherwise returns 0.
*/

int		ft_exist(char *varname, char **env)
{
	int		len;
	char	*tmpvar;

	tmpvar = ft_strjoin(varname, "=");
	len = ft_strlen(tmpvar);
	while (*env)
	{
		if (ft_strncmp(*env, tmpvar, len) == 0)
		{
			ft_strdel(&tmpvar);
			return (1);
		}
		env++;
	}
	ft_strdel(&tmpvar);
	return (0);
}

/*
** ft_isempty :
** Returns -1 if varname does not exist.
** Returns 1 if the variable varname is empty (ex: "PATH=").
** Otherwise, returns 0.
*/

int		ft_isempty(char *varname, char **env)
{
	char	*tmp;

	if (ft_exist(varname, env) == 0)
		return (-1);
	tmp = ft_get_envvar(varname, env);
	while (*tmp && *tmp != '=')
		tmp++;
	if (*tmp == '\0')
		return (1);
	return (0);
}

/*
** ft_get_envvar :
** Returns the variable varname in **env
*/

char	*ft_get_envvar(char *varname, char **env)
{
	int		i;
	int		len;
	char	*tmpvar;

	if (ft_exist(varname, env) == 0)
		return (NULL);
	tmpvar = ft_strjoin(varname, "=");
	len = ft_strlen(tmpvar);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tmpvar, len) == 0)
		{
			ft_strdel(&tmpvar);
			return (*(env + i));
		}
		i++;
	}
	ft_strdel(&tmpvar);
	return (NULL);
}
