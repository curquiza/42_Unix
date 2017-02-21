/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:19:59 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/03 13:03:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


void	ft_childprocess(t_command *com, char **path, char **env)
{
	char		*compath;
	int			i;
	char		*tmp;

	compath = NULL;
	i = 0;
	execve(com->bin, com->arg, env);
	while (path[i])
	{
		tmp = compath;
		compath = ft_strnew(ft_strlen(path[i]) + ft_strlen(com->bin) + 1);
		ft_strdel(&tmp);
		ft_strcat(ft_strcat(ft_strcpy(compath, path[i]), "/"), com->bin);
		execve(compath, com->arg, env);
		i++;
	}
	if (i == ft_tablen(path))
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(com->bin, 2);
		exit(1);
	}
}

int		main(int ac, char **av, char **environ)
{
	char 		**env;
	t_command	**com;
	char		*line;
	pid_t		process;
	char		**path;

	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("Error : number of arguments", 2);
		return (1);
	}
	env = ft_tabdup(environ);
	path = ft_get_path(env);
	while (42)
	{
		ft_putstr_col(PROMPT, B_CYAN, DEF);
		if (get_next_line(1, &line) == -1)
			return (1);
		if (!(com = ft_get_commands(line)))
			continue ;
		while (*com)
		{
			if (ft_strcmp((*com)->bin, "exit") == 0)
				exit(1);
			if ((process = fork()) == -1)
			{
				ft_putendl("Fork error");
				return (1);
			}
			if (process > 0)
				wait(NULL);
			else
				ft_childprocess(*com, path, env);
			com++;
		}
	}
	return (0);
}
