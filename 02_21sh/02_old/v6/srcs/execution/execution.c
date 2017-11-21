/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/30 16:51:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_pre_execution(t_ast *ast)
{
	if (ast)
	{
		ft_semantic_analysis(ast);
		ft_expansion(ast);
		ft_get_argtab(ast);
		ft_build_redir_list(ast);
	}
}

int		ft_execution(t_ast *ast)
{
	int		ret_cmd;

 	if (ast)
	{
		if (ast->lex && ast->lex->op == SEMIC)
			return (ft_apply_semic(ast));
		else if (ast->lex && ast->lex->op == DPIPE)
			return (ft_apply_d_pipe(ast));
		else if (ast->lex && ast->lex->op == DAND)
			return (ft_apply_d_and(ast));
		else if (ast->lex && ast->lex->op == PIPE)
			return (ft_apply_pipe(ast));
		else
		{
			ret_cmd = ft_fork_and_exec(ast);
			ft_fill_cmd_return(ret_cmd, ast->shell);
			return (ret_cmd);
		}
	}
	return (CMD_SUCCESS);
}

void	ft_cmd_line_execution(t_ast **ast, t_shell *shell)
{
	if (shell->flags->token || shell->flags->ast)
		ft_putendl_col("\n---- EXEC ----\n", B_YELLOW, DEF);
	ft_fill_cmd_return(ft_execution(*ast), shell);
	if (shell->flags->token || shell->flags->ast)
		ft_putendl_col("\n--------------\n", B_YELLOW, DEF);
	ft_del_ast(ast);
}
