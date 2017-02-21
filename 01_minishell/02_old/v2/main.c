/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:19:59 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/04 17:44:14 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_callbuiltin_if(t_command *com, char **env)
{
	if (ft_strcmp(com->arg[0], "echo") == 0)
		ft_echo(com->arg);
	else if (ft_strcmp(com->arg[0], "cd") == 0)
		exit(0);
	else if (ft_strcmp(com->arg[0], "env") == 0)
		ft_env(com->arg, env);
	else if (ft_strcmp(com->arg[0], "setenv") == 0)
		exit(0);
	else if (ft_strcmp(com->arg[0], "unsetenv") == 0)
		exit(0);
}

void	ft_childprocess(t_command *com, char **path, char **env)
{
	char	*compath;
	int		i;

	ft_callbuiltin_if(com, env);
	execve(com->bin, com->arg, env);
	compath = NULL;
	i = 0;
	while (path[i])
	{
		ft_strdel(&compath);
		compath = ft_strnew(ft_strlen(path[i]) + ft_strlen(com->bin) + 1);
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



void	ft_exit_if(char *bin, t_command **com)
{
	if (ft_strcmp(bin, "exit") == 0)
	{
		ft_comdel(&com);
		while(1);
		exit(1);
	}
}


void	ft_exec_allcom(t_command **com, char **path, char **env)
{
	int		i;
	pid_t	process;

	i = 0;
	while (com[i])
	{
		ft_exit_if(com[i]->bin, com);
		if ((process = fork()) == -1)
		{
			ft_comdel(&com);
			ft_putendl("Fork error");
			return ;
		}
		if (process > 0)
			wait(NULL);
		else
			ft_childprocess(com[i], path, env);
		i++;
	}
}

int		main(int ac, char **av, char **environ)
{
	char 		**env;
	t_command	**com;
	char		*line;
	char		**path;

	(void)ac;
	(void)av;
	env = ft_tabdup(environ);
	ft_init_shlvl(env);
	path = ft_get_path(env);
	com = NULL;
	line = NULL;
	while (42)
	{
		ft_putstr_col(PROMPT, B_CYAN, DEF);
		ft_strdel(&line);
		ft_comdel(&com);
		if (get_next_line(1, &line) == -1)
			return (1);
		if (!(com = ft_get_commands(line)))
			continue ;
		ft_exec_allcom(com, path, env);
	}
	return (0);
}
