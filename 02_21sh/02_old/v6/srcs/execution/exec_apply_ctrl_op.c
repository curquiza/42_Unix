#include "shell.h"

int		ft_apply_semic(t_ast *ast)
{
	int		ret;
	
	ret = CMD_SUCCESS;
	if (ast->left)
		ret = ft_execution(ast->left);
	if (ast->right)
		ret = ft_execution(ast->right);
	return (ret);
}

/*int		ft_right_pipe(int pfd[2], int left, t_ast *ast_right)
{
	int		right;
	int		ret;

	ret = CMD_SUCCESS;
	if (!ast_right)
		return (ret);
	if ((right = fork()) == -1)
		ft_put_errmsg(ast_right->shell->name, NULL, "fork error");
	else if (right == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		if (ast_right->lex && ast_right->lex->op == PIPE)
			exit(ft_execution(ast_right));
		ft_pre_execution(ast_right);
		exit(ft_exec_simple_cmd(ast_right));
	}
	else if (right > 0)
	{
		waitpid(left, NULL, WNOHANG);
		close(pfd[1]);
		waitpid(right, &ret, 0);
		close(pfd[0]);
	}
	return (ret);
}

int		ft_apply_pipe(t_ast *ast)
{
	int		pfd[2];
	int		left;
	int		ret;

	ret = CMD_SUCCESS;
	if (ast)
	{
		if (pipe(pfd) == -1)
			ft_put_errmsg(ast->shell->name, NULL, "pipe error");
		if ((left = fork()) == -1)
			ft_put_errmsg(ast->shell->name, NULL, "fork error");
		else if (left == 0)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			ft_pre_execution(ast->left);
			exit(ft_exec_simple_cmd(ast->left));
		}
		else if (left > 0)
		{
			ret = ft_right_pipe(pfd, left, ast->right);
			wait(NULL);
		}
	}
	return (ft_get_cmdret(ret));
}*/

void	ft_left_pipe(int pfd[2], t_ast *ast_left)
{
	int		left;

	if (!ast_left)
		return ;
	if ((left = fork()) == -1)
		ft_put_errmsg(ast_left->shell->name, NULL, "fork error");
	else if (left == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		if (ast_left->lex && ast_left->lex->op == PIPE)
			exit(ft_execution(ast_left));
		ft_pre_execution(ast_left);
		exit(ft_exec_simple_cmd(ast_left));
	}
	else if (left > 0)
	{
		waitpid(left, NULL, WNOHANG);
		close(pfd[1]);
	}
}

int		ft_apply_pipe(t_ast *ast)
{
	int		pfd[2];
	int		right;
	int		ret;

	ret = CMD_SUCCESS;
	if (ast)
	{
		if (pipe(pfd) == -1)
			ft_put_errmsg(ast->shell->name, NULL, "pipe error");
		if ((right = fork()) == -1)
			ft_put_errmsg(ast->shell->name, NULL, "fork error");
		else if (right == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			ft_pre_execution(ast->right);
			exit(ft_exec_simple_cmd(ast->right));
		}
		else if (right > 0)
		{
			ft_left_pipe(pfd, ast->left);
			waitpid(right, &ret, 0);
			close(pfd[0]);
			wait(NULL);
		}
	}
	return (ft_get_cmdret(ret));
}

int		ft_apply_d_pipe(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if ((ret = ft_execution(ast->left)) != 0)
		ret = ft_execution(ast->right);
	//else
	//{
	//	ast = ast->right;
	//	while (ast && ast->lex && ast->lex->op != DAND)
	//		ast = ast->right;
	//	if (ast && ast->lex && ast->lex->op == DAND)
	//		ret = ft_execution(ast);
	//}
	return (ret);
}

int		ft_apply_d_and(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if ((ret = ft_execution(ast->left)) == 0)
		ret = ft_execution(ast->right);
	//else
	//{
	//	ast = ast->right;
	//	while (ast && ast->lex && ast->lex->op != DPIPE)
	//		ast = ast->right;
	//	if (ast && ast->lex && ast->lex->op == DPIPE)
	//		ret = ft_execution(ast);
	//}
	return (ret);
}
