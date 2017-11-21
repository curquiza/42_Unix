/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/17 11:48:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_apply_semic(t_ast *ast, t_var *vartab)
{
	if (ast->left)
		ft_execution(ast->left, vartab);
	if (ast->right)
		ft_execution(ast->right, vartab);
}

void	ft_apply_pipe(t_ast *ast, t_var *vartab)
{
	pid_t	pid;
	int		pfd[2];

	if (pipe(pfd) == -1)
		ft_put_errmsg("21sh", NULL, "pipe error");
	//if ((pid = fork()) == -1)
	//	ft_put_errmsg("21sh", NULL, "fork error");
	//if (pid == 0)
	//{
		if (ast->left)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			close(pfd[1]);
			ft_execution(ast->left, vartab);
		//	exit(0);
		}
		//exit(0);
//	}
	//else if (pid > 0)
	//{
		if (ast->right)
		{
			wait(&pid);
			close(pfd[1]);
			dup2(pfd[0], 0);
			close(pfd[0]);
			ft_execution(ast->right, vartab);
		//	exit(0);
	//	}
		//exit(0);
	}
}

void	ft_execution(t_ast *ast, t_var *vartab)
{
 	if (ast)
	{
		if (ast->lex && ast->lex->token == SEMIC)
			ft_apply_semic(ast, vartab);
		else if (ast->lex && ast->lex->token == PIPE)
			ft_apply_pipe(ast, vartab);
		else
			ft_exec_simple_cmd(ast, vartab);
	/*	else if (ast->left)
			ft_execution(ast->left, vartab);
		else if (ast->right)
			ft_execution(ast->right, vartab);*/
	}
}

/*void	ft_execution2(t_ast *ast, t_var *vartab)
{
	if (ast)
	{
		if (!ast->left && !ast->right)
		{
			ft_exec_simple_cmd(ast, vartab);
			return ;
		}
		else
			ft_execution(ast, vartab);
	}
}*/

/*void	ft_execution(t_ast *ast, t_var *vartab)
{
	if (ast)
	{
		if (ast->cmd && ft_exec_simple_cmd(ast, vartab) != 0)
		{
			if (ast->cmd)
				ft_putendl2_fd(ast->cmd->s, " : NO exec", 1);
			else if (ast->lex)
				ft_putendl2_fd(ast->lex->s, " : NO exec", 1);
			return ;
		}
		if (!ast->cmd)
			ft_putendl2_fd(ast->lex->s, " : NO exec", 1);
		else
			ft_putendl2_fd(ast->cmd->s, " : exec", 1);
	}
}*/
