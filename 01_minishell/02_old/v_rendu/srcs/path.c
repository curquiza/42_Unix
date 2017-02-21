/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:37:34 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/10 14:03:00 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_get_path(char **env)
{
	char	*line;

	line = ft_get_envvar("PATH", env);
	if (line == NULL)
		return (NULL);
	return (ft_strsplit(line + 5, ':'));
}

int		ft_noaccess(char *path)
{
	struct stat	*info;

	if (!(info = (struct stat *)malloc(sizeof(*info))))
		return (0);
	if (lstat(path, info) != -1 && access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		if (ft_strrchr(path, '/'))
			ft_putendl_fd(ft_strrchr(path, '/') + 1, 2);
		else
			ft_putendl_fd(path, 2);
		free(info);
		return (1);
	}
	free(info);
	return (0);
}

int		ft_fileserr(char *path)
{
	struct stat	*info;

	if (!(info = (struct stat *)malloc(sizeof(*info))))
		return (0);
	if (ft_strchr(path, '/') != NULL)
	{
		if (lstat(path, info) == -1)
			ft_putstr_fd("minishell: no such file or directory: ", 2);
		else
			ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(path, 2);
		free(info);
		return (1);
	}
	free(info);
	return (0);
}

void	ft_comnotfound(char *bin)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(bin, 2);
}
