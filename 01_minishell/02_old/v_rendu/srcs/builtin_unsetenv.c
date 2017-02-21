/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 12:11:27 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/08 12:20:19 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_unsetenv_newenv(char *var, char **env)
{
	int		i;
	int		j;
	int		len;
	char	**newenv;

	if (!(newenv = (char **)malloc(sizeof(*newenv) * ft_tablen(env))))
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) != 0)
		{
			newenv[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	newenv[j] = NULL;
	return (newenv);
}

void	ft_unsetenv(char **arg, char ***env)
{
	char	*tmpvar;
	char	**tmpenv;

	if (ft_tablen(arg) == 1)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
	{
		while (*arg)
		{
			if (ft_exist(*arg, *env) == 1)
			{
				tmpvar = ft_strjoin(*arg, "=");
				tmpenv = *env;
				*env = ft_unsetenv_newenv(tmpvar, tmpenv);
				ft_strdel(&tmpvar);
				ft_tabdel(&tmpenv);
			}
			arg++;
		}
	}
}
