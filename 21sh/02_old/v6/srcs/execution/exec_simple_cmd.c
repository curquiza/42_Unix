/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:37:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/06/01 10:37:50 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_exec_simple_cmd(t_ast *ast)
{
	if (ast)
	{
		ft_do_ass_word(ast, 1);
		if (ast->redir_list
			&& ft_do_redirection(ast->redir_list, ast->shell) == -1)
			return (CMD_FAILURE);
		return (ft_do_cmd(ast));
	}
	return (CMD_SUCCESS);
}

int		ft_fork_and_exec(t_ast *ast)
{
	pid_t	pid;
	int		ret;
	int		builtin_ret;

	ret = CMD_SUCCESS;
	if (ast)
	{
		ft_pre_execution(ast);
		if (!ast->cmd)
			ft_do_ass_word(ast, 0);
		//if (ast->cmd && (builtin_ret = ft_is_built_in(ast->cmd->s)) != NOT_BUILTIN)
		//	return (ft_exec_built_in(ast, builtin_ret));
		if ((pid = fork()) == -1)
			ft_put_errmsg(ast->shell->name, NULL, "fork error");
		else if (pid == 0)
			exit(ft_exec_simple_cmd(ast));
		else if (pid > 0)
			wait(&ret);
		if (ret == 0 && ast->cmd
			&& (builtin_ret = ft_is_special_built_in(ast->cmd->s)))
			return (ft_exec_built_in(ast, builtin_ret));
	}
	return (ft_get_cmdret(ret));
}
