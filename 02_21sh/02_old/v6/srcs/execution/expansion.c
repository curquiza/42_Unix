/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:48:16 by curquiza          #+#    #+#             */
/*   Updated: 2017/06/01 12:20:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*void	ft_expansion(t_ast *ast)
{
	int		ind_empty;

	t_lexeme	*current;

	if (ast)
	{
		ind_empty = 0;
		current = ast->lex;
		while (current)
		{
			if (current->token == WORD || current->token == ASS_WORD)
			{
				ft_tilde_expansion(&current->s, shell);
				ft_parameter_expansion(&current->s, ast->shell);
				ft_quote_removal(&current->s);
				if (ft_strcmp(current->s, "") == 0)
					ind_empty = 1;
			}
			current = current->next;
		}
		//if (ind_empty == 1)
		//	ft_lexlst_remove_if(&ast->lex, "", 0);
		if (ast->left)
			ft_expansion(ast->left);
		if (ast->right)
			ft_expansion(ast->right);
	}
}*/

/*void	ft_apply_expansion_on(t_lexeme **lex, t_shell *shell, int rm_mode)
{
	int			ind_empty;
	t_lexeme	*current;

	ind_empty = 0;
	current = *lex;
	while (current)
	{
		if (current->token == WORD || current->token == ASS_WORD)
		{
			ft_tilde_expansion(&current->s, shell);
			ft_parameter_expansion(&current->s, shell);
			ft_quote_removal(&current->s);
			if (ft_strcmp(current->s, "") == 0)
				ind_empty = 1;
		}
		current = current->next;
	}
	if (rm_mode == 1 && ind_empty == 1)
		ft_lexlst_remove_if(lex, "", 0);
}*/

void	ft_apply_expansion_on(t_lexeme **lex, t_shell *shell)
{
	t_lexeme	*current;

	current = *lex;
	while (current)
	{
		if (current->token == WORD || current->token == ASS_WORD)
		{
			ft_tilde_expansion(&current->s, shell);
			ft_parameter_expansion(&current->s, shell);
			ft_quote_removal(&current->s);
		}
		current = current->next;
	}
}

void	ft_expansion(t_ast *ast)
{
	if (ast)
	{
		ft_apply_expansion_on(&ast->ass_word, ast->shell);
		ft_apply_expansion_on(&ast->cmd, ast->shell);
		ft_apply_expansion_on(&ast->lex, ast->shell);
		ft_apply_expansion_on(&ast->redir, ast->shell);
	}
}
