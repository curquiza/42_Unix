/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 19:58:50 by curquiza         ###   ########.fr       */
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

//pour mettre a la norme => ft_exec_simple_cmd
// peut se mettre dans ft_apply_pipe aussi
// attention au retour de commande
void	ft_right_pipe(int pfd[2], int left, t_ast *ast_right, t_var *vartab)
{
	int		right;

	if ((right = fork()) == -1)
		ft_put_errmsg("21sh", NULL, "fork error");
	else if (right == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		if (ast_right->lex && ast_right->lex->op == PIPE)
		{
			//ft_apply_pipe(ast_right, vartab);
			ft_execution(ast_right, vartab);
			exit(1);
		}
		else
		{
			//ft_load_simple_cmd(ast_right, vartab);
			//if (ast_right && ast_right->cmd)
			//	execve(ast_right->cmd->s, ast_right->argtab, vartab->env);
			//exit(1);
			//exit(ft_exec_scmd_in_pipe(ast_right, vartab));
			exit(ft_exec_simple_cmd(ast_right, vartab));
		}
	}
	else if (right > 0)
	{
		(void)left;
		//waitpid(left, NULL, 0);
		waitpid(left, NULL, WNOHANG);
		close(pfd[1]);
		waitpid(right, NULL, 0);
		close(pfd[0]);
	}
}

void	ft_apply_pipe(t_ast *ast, t_var *vartab)
{
	int		pfd[2];
	int		left;

	if (ast)
	{
		if (pipe(pfd) == -1)
			ft_put_errmsg("21sh", NULL, "pipe error");
		if ((left = fork()) == -1)
			ft_put_errmsg("21sh", NULL, "fork error");
		else if (left == 0)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			//ft_load_simple_cmd(ast->left, vartab);
			//if (ast->left && ast->left->cmd)
			//	execve(ast->left->cmd->s, ast->left->argtab, vartab->env);
			//exit(0);
			//exit(ft_exec_scmd_in_pipe(ast->left, vartab));
			exit(ft_exec_simple_cmd(ast->left, vartab));
		}
		else if (left > 0)
		{
			ft_right_pipe(pfd, left, ast->right, vartab);
			wait(NULL);
		}
	}
}

void	ft_execution(t_ast *ast, t_var *vartab)
{
 	if (ast)
	{
		if (ast->lex && ast->lex->op == SEMIC)
			ft_apply_semic(ast, vartab);
		else if (ast->lex && ast->lex->op == PIPE)
			ft_apply_pipe(ast, vartab);
		else
		{
		//	ft_load_simple_cmd(ast, vartab);
		//	if (ast->cmd)
		//		ft_fork_and_exec(ast, vartab);
			//ft_exec_scmd(ast, vartab);
			ft_fork_and_exec(ast, vartab);
		}
	}
}
