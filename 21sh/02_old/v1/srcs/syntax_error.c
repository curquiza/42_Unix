/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:38:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/24 16:39:38 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_puterr_unexp_token(char *token)
{
	ft_putstr_fd("21sh: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("\'", 2);
}

t_lexeme	*ft_next_token(t_lexeme *lex)
{
	lex = lex->next;
	while (lex && lex->token == NEWLINE)
		lex = lex->next;
	return (lex);
}

char	*ft_check_tokenerror(t_lexeme *lex)
{
	t_lexeme	*next_tok;

	if (lex && lex->token == CTRL_OP)
		return (lex->s);
	while (lex)
	{
		if (lex->token == RED_OP && lex->next
			&& lex->next->token != WORD && lex->next->token != NAME)
			return (lex->next->s);
		if (lex->op == DSEMIC || lex->op == DPIPE
			|| lex->op == AND || lex->op == DAND)
			return (lex->s);
		if (lex->token == CTRL_OP && (next_tok = ft_next_token(lex))
			&& next_tok->token == CTRL_OP)
			return (next_tok->s);
		lex = lex->next;
	}
	return (NULL);
}
