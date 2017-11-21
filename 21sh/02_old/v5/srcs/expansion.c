/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:48:16 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:47:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_expansion(t_ast *ast)
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
}
