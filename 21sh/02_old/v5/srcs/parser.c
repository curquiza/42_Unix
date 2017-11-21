/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 19:19:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:37:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_parser :
** Check les erreurs de syntax.
** Gère les inhibiteurs.
** Supprime les tokens de type NEWLINE.
** Récupère les arguments du hdoc.
** Renvoie -1 si syntax error, 0 sinon.
*/

int		ft_parser(t_lexeme **lex, t_shell *shell)
{
	char	        *tokenerror;
    enum e_token    newline;

	if (!lex)
		return (0);
	if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
	{
		ft_puterr_unexp_token(tokenerror);
		return (-1);
	}
	if (ft_inhibitor(lex) == -1)
		return (-1);
    newline = NEWLINE;
	ft_lexlst_remove_if(lex, &newline, 1);
	ft_hdoc(*lex, shell);

	// if (shell->flag->token == 1)
	ft_put_lexlst(*lex);

	return (0);
}

/*int		ft_parser(t_lexeme **lex, t_shell *shell)
{
	char	        *tokenerror;
    enum e_token    newline;

	if (!lex)
		return (-1); //0
	if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
	{
		ft_puterr_unexp_token(tokenerror);
		return (-1); //258
	}
	if (ft_inhibitor(lex) == -1)
		return (-1); //258
    newline = NEWLINE;
	ft_lexlst_remove_if(lex, &newline, 1);
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
