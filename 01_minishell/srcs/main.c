/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:19:59 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/21 13:37:23 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_childprocess(t_command *com, char **env)
{
	char	*compath;
	int		i;
	char	**path;

	if (ft_noaccess(com->bin) == 1)
		exit(1);
	execve(com->bin, com->arg, env);
	if (ft_fileserr(com->bin) == 1)
		exit(1);
	path = ft_get_path(env);
	i = -1;
	compath = NULL;
	while (path && path[++i])
	{
		ft_strdel(&compath);
		compath = ft_strjoin3(path[i], "/", com->bin);
		if (ft_noaccess(compath) == 1)
			break ;
		execve(compath, com->arg, env);
	}
	if (i == -1 || i == ft_tablen(path))
		ft_comnotfound(com->bin);
	ft_strdel(&compath);
	ft_tabdel(&path);
	exit(1);
}

void	ft_exec_allcom(t_command **com, char ***env)
{
	int		i;
	pid_t	process;

	i = -1;
	while (com[++i])
	{
		if (ft_exit_if(com[i]->bin, com) == -1)
			return ;
		ft_signal_minishell(com[i]->bin);
		if (ft_callbuiltin_if(com[i], env) == 0)
		{
			if ((process = fork()) == -1)
			{
				ft_comdel(&com);
				ft_putendl("minishell: Fork error");
				return ;
			}
			if (process > 0)
				wait(NULL);
			else
				ft_childprocess(com[i], *env);
		}
	}
}

int		main(int ac, char **av, char **environ)
{
	char		**env;
	t_command	**com;
	char		*line;

	(void)ac;
	(void)av;
	com = NULL;
	line = NULL;
	ft_initenv(&env, environ);
	while (42)
	{
		ft_putprompt(env);
		ft_strdel(&line);
		ft_comdel(&com);
		ft_signal_ctrlc(env);
		if (get_next_line(1, &line) == -1)
			return (1);
		if (!(com = ft_get_commands(line)))
			continue ;
		ft_exec_allcom(com, &env);
	}
	return (0);
}
