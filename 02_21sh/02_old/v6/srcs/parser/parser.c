/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 19:19:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/10 17:24:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_parser :
** Check les erreurs de syntax.
** Gère les inhibiteurs.
** Supprime les tokens de type NEW_LINE.
** Récupère les arguments du hdoc.
** Renvoie -1 si syntax error, 0 sinon.
*/

int		ft_parser(t_lexeme **lex, t_shell *shell)
{
	char	        *tokenerror;
    enum e_token    new_line;

	if (!lex)
		return (0);
	if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
	{
		ft_puterr_unexp_token(tokenerror, shell->name);
		return (-1);
	}
	if (ft_inhibitor(lex, shell) == -1)
		return (-1);
    new_line = NEW_LINE;
	ft_lexlst_remove_if(lex, &new_line, 1);
	ft_hdoc(*lex, shell);
	if (shell->flags->token == 1)
		ft_put_lexlst(*lex);
	return (0);
}

/*int		ft_parser(t_lexeme **lex, t_shell *shell)
{
	char	        *tokenerror;
    enum e_token    new_line;

	if (!lex)
		return (-1); //0
	if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
	{
		ft_puterr_unexp_token(tokenerror);
		return (-1); //258
	}
	if (ft_inhibitor(lex) == -1)
		return (-1); //258
    new_line = NEW_LINE;
	ft_lexlst_remove_if(lex, &new_line, 1);
    if (!*lex)
    {
        ft_putendl_fd("no cmd", 2);
        return (-1); // 0
    }
	ft_hdoc(*lex, shell);

	ft_putendl("\n--- TOKENS ---\n");
	ft_put_lexlst(*lex);
	ft_putendl("--------------");

	return (0);
}*/
