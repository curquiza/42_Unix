/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 21:47:29 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/13 19:26:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_inhibitor :
** Vérifie les fermetures de doubles et simples quotes, et des back-slashs.
** Rend la main à l'utilisateur si nécessaire => vérifie donc à chaque fois les
** erreurs de syntaxe, et split la chaine de char récupérée dans les bons
** maillons.
*/

int		ft_inhibitor(t_lexeme **lex)
{
	char	*tokenerror;
	int		ind_quote;
	int		ind_bslash;
	char	*line;

	ind_bslash = 0;
	line = NULL;
	while ((ind_quote = ft_check_quote(*lex)) != 0 || ft_check_pipe(*lex) == -1
			|| (ind_bslash = ft_check_bslash(*lex)) == -1)
	{
		if (ind_quote != 0)
			ft_putstr("quote> ");
		else if (ind_bslash != 0)
			ft_putstr("bslash> ");
		else
			ft_putstr("pipe> ");
		ft_read_command_newline(&line);
		if (ind_quote != 0)
			ft_add_endoftoken_quote(*lex, &line, ind_quote);
		else if (ind_bslash != 0)
			ft_add_endoftoken_bslash(*lex, &line);
		ft_lexer(lex, line);
		ft_lexlst_remove_if(lex, "", 0);
		if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
		{
			ft_puterr_unexp_token(tokenerror);
			free(line);
			return (-1);
		}
		ind_bslash = 0;
	}
	free(line);
	return (0);
}
