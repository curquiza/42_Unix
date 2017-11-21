/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 19:19:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/13 17:45:14 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_parser :
** Check les erreurs de syntax.
** Gère les inhibiteurs.
** Supprime les tokens de type NEWLINE.
** Récupère les arguments du hdoc.
*/

int		ft_parser(t_lexeme **lex, t_var *tabvar)
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
	ft_hdoc(*lex, tabvar);

	ft_putendl("\n--- TOKENS ---\n");
	ft_put_lexlst(*lex);
	ft_putendl("--------------");

	return (0);
}
