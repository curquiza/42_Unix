/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:49:48 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/20 11:05:28 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_cd_puterr(char *path, char *message)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
}

int		ft_cd_checkerrors(char *path)
{
	struct stat		*info;

	if (!(info = (struct stat *)malloc(sizeof(*info))))
		return (1);
	if (lstat(path, info) == -1)
	{
		ft_cd_puterr(path, "No such file or directory");
		free(info);
		return (1);
	}
	else if (S_ISDIR(info->st_mode) != 1)
	{
		ft_cd_puterr(path, "Not a directory");
		free(info);
		return (1);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_cd_puterr(path, "Permission denied");
		free(info);
		return (1);
	}
	free(info);
	return (0);
}

int		ft_gotodir(char *path, char ***env)
{
	char	*pwd;

	if (ft_cd_checkerrors(path) == 1)
		return (1);
	pwd = getcwd(NULL, 0);
	ft_change_env2(env, "OLDPWD", pwd);
	ft_strdel(&pwd);
	chdir(path);
	pwd = getcwd(NULL, 0);
	ft_change_env2(env, "PWD", pwd);
	ft_strdel(&pwd);
	return (0);
}

void	ft_cd(char **arg, char ***env)
{
	char	*tmp;

	if (ft_tablen(arg) == 1)
	{
		if (ft_exist("HOME", *env) == 0 || ft_isempty("PWD", *env) == 1)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		else
			ft_gotodir(ft_get_envvar("HOME", *env) + 5, env);
	}
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		if (ft_exist("OLDPWD", *env) == 0 || ft_isempty("OLDPWD", *env) == 1)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
		{
			tmp = ft_strdup(ft_get_envvar("OLDPWD", *env) + 7);
			if (ft_gotodir(tmp, env) == 0)
				ft_putendl(tmp);
			ft_strdel(&tmp);
		}
	}
	else
		ft_gotodir(arg[1], env);
}
