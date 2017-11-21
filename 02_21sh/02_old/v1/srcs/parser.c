/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 19:19:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/03 12:31:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_parser(t_lexeme **lex, t_ast **ast)
{
	char	        *tokenerror;
    enum e_token    newline;

	if (!lex)
		return (-1);
	if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
	{
		ft_puterr_unexp_token(tokenerror);
		return (-1);
	}
	if (ft_inhibitor(lex) == -1)
		return (-1);
    newline = NEWLINE;
	ft_lexlst_remove_if(lex, &newline, 1);
    if (!*lex)
    {
        ft_putendl_fd("no cmd", 2);
        return (-1);
    }
	//ft_apply_bslash(*lex);
	//ft_apply_quote(*lex);
	ft_ast(*lex, ast);
	return (0);
}
