/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:47:36 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/05 19:40:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_varvalue(char **tabvar, char *varname)
{
	int		len;
	int		varlen;

	if (tabvar)
	{
		varlen = ft_strlen(varname);
		while (*tabvar)
		{
			len = 0;
			while ((*tabvar)[len] && (*tabvar)[len] != '=')
				len++;
			if (len == varlen && ft_strncmp(*tabvar, varname, len) == 0)
				return (ft_strchr(*tabvar, '=') + 1);
			tabvar++;
		}
	}
	return (NULL);
}

int		ft_get_varindex(char **tabvar, char *varname)
{
	int		len;
	int		index;
	int		varlen;

	if (tabvar)
	{
		varlen = ft_strlen(varname);
		index = 0;
		while (*tabvar)
		{
			len = 0;
			while (tabvar[index][len] && tabvar[index][len] != '=')
				len++;
			if (len == varlen && ft_strncmp(tabvar[index], varname, len) == 0)
				return (index);
			index++;
		}
	}
	return (-1);
}

int		ft_exist_in(char **tabvar, char *varname)
{
	int		varlen;
	int		len;

	if (tabvar)
	{
		varlen = ft_strlen(varname);
		while (*tabvar)
		{
			len = 0;
			while ((*tabvar)[len] && (*tabvar)[len] != '=')
				len++;
			if (varlen == len && ft_strncmp(*tabvar, varname, len) == 0)
				return (1);
			tabvar++;
		}
	}
	return (0);
}

char	**ft_add_envvar(char ***env, char *newvar, char *value)//a verif
{
	char	**tmpenv;
	int		i;

	if (!(tmpenv = (char **)malloc(sizeof(**env) * (ft_tablen(*env) + 2))))
		ft_exit("malloc error", 1);
	i = 0;
	while ((*env)[i])
	{
		tmpenv[i] = (*env)[i];
		i++;
	}
	if (value == NULL)
		tmpenv[i] = ft_strdup(newvar);
	else
		tmpenv[i] = ft_strjoin3(newvar, "=", value);
	tmpenv[i + 1] = NULL;
	free(*env);
	return (tmpenv);
}

void	ft_change_envvar(char **env, char *newvar, char *value) 
{
	char	*name;
	int		len;
	int		index;

	if (value == NULL)
	{
		len = 0;
		while (newvar[len] && newvar[len] != '=')
			len++;
		name = ft_strsub(newvar, 0, len);
	}
	else
		name = newvar;
	index = ft_get_varindex(env, name);
	free(env[index]);
	if (value == NULL)
	{
		env[index] = ft_strdup(newvar);
		free(name);
	}
	else
		env[index] = ft_strjoin3(newvar, "=", value);
}

void	ft_modif_env(char ***env, char *newvar, char *value)
{
	int		len;
	char	*tmpvar;

	len = 0;
	if (value == NULL)
	{
		while (newvar[len] && newvar[len] != '=')
			len++;
		tmpvar = ft_strsub(newvar, 0, len);
	}
	else
		tmpvar = newvar;
	if (ft_exist_in(*env, tmpvar) == 1)
		ft_change_envvar(*env, newvar, value);
	else
		*env = ft_add_envvar(env, newvar, value);
	if (value == NULL)
		ft_strdel(&tmpvar);
}

t_var	*ft_init_tabvar(char **environ)
{
	t_var		*tabvar;

	if (!(tabvar = (t_var *)malloc(sizeof(*tabvar))))
		ft_exit("malloc error", 1);
	tabvar->local = NULL;
	tabvar->env = ft_init_env(environ);
	return (tabvar);
}

char	**ft_init_env(char **environ)
{
	char	**env;
	char	*charval;
	int		intval;
	char	*pwd;

	env = ft_tabdup(environ);
	intval = 0;
	charval = ft_get_varvalue(env, "SHLVL");
	if (charval)
		intval = ft_atoi(charval);
	intval++;
	charval = ft_itoa(intval);
	ft_modif_env(&env, "SHLVL", charval);
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_modif_env(&env, "PWD", pwd);
	else
		ft_modif_env(&env, "PWD", "");
	free(pwd);
	free(charval);
	return (env);
}

/*int		main(int ac, char **av, char **environ)
{
	char	**env;

	env = ft_tabdup(environ);
	ft_init_env(&env);
	if (ac == 3)
		ft_modif_env(&env, av[1], av[2]);
	else if (ac == 2 && ft_strchr(av[1], '=') == NULL)
		ft_modif_env(&env, av[1], "");
	else if (ac == 2)
		ft_modif_env(&env, av[1], NULL);
	ft_puttab(env);
	while (1);
	return (0);
}*/
