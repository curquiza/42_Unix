/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:37:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:54:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_get_cmdret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		ft_putendl("\n/!\\ /!\\ Processus fils fermé par un signal /!\\ /!\\");
		if (WTERMSIG(status) == SIGSEGV)
			ft_putendl("=> SEGFAULT");
		if (WTERMSIG(status) == SIGABRT)
			ft_putendl("=> SIGABORT");
		else
			ft_putnbr2("signal = ", WTERMSIG(status));
	}
	return (CMD_FAILURE);
}

int		ft_exec_simple_cmd(t_ast *ast)
{
	if (ast)
	{
		ft_do_ass_word(ast, 1);
		if (ast->redir_list && ft_do_redirection(ast->redir_list) == -1)
			return (CMD_FAILURE);
		return (ft_do_cmd(ast));
	}
	return (CMD_SUCCESS);
}

int		ft_fork_and_exec(t_ast *ast)
{
	pid_t	pid;
	int		ret;

	ret = CMD_SUCCESS;
	if (ast)
	{
		if (!ast->cmd)
			ft_do_ass_word(ast, 0);
		if ((pid = fork()) == -1)
			ft_put_errmsg("21sh", NULL, "fork error");
		else if (pid == 0)
			exit(ft_exec_simple_cmd(ast));
		else if (pid > 0)
			wait(&ret);
	}
	return (ft_get_cmdret(ret));
}
