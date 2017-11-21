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

int		ft_right_pipe(int pfd[2], int left, t_ast *ast_right)
{
	int		right;
	int		ret;

	ret = CMD_SUCCESS;
	if ((right = fork()) == -1)
		ft_put_errmsg("21sh", NULL, "fork error");
	else if (right == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		if (ast_right->lex && ast_right->lex->op == PIPE)
			exit(ft_execution(ast_right));
		else
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
			ft_put_errmsg("21sh", NULL, "pipe error");
		if ((left = fork()) == -1)
			ft_put_errmsg("21sh", NULL, "fork error");
		else if (left == 0)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			exit(ft_exec_simple_cmd(ast->left));
		}
		else if (left > 0)
		{
			ret = ft_right_pipe(pfd, left, ast->right);
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
	return (ret);
}

int		ft_apply_d_and(t_ast *ast)
{
	int		ret;

	ret = CMD_SUCCESS;
	if ((ret = ft_execution(ast->left)) == 0)
		ret = ft_execution(ast->right);
	return (ret);
}
