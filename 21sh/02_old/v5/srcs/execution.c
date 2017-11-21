/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/28 00:03:58 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_execution(t_ast *ast)
{
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
			return (ft_fork_and_exec(ast));
	}
	return (CMD_SUCCESS);
}

void	ft_cmd_line_execution(t_ast **ast, t_shell *shell)
{
	char	*ret_char;

	ret_char = ft_itoa(ft_execution(*ast));
	ft_chg_varval_or_add(&shell->var_priv, "?", ret_char);
	ft_del_ast(ast);
	ft_strdel(&ret_char);
}
