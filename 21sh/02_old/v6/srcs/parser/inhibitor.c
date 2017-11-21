/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 21:47:29 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/30 19:05:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_read_line_again :
** Affiche le prompt correspondant à l'inhibiteur et récupère la nouvelle entrée
** de l'utilisateur.
*/

void	ft_read_line_again(enum e_inhib inhib, char **line)
{
	char	*prompt;

	if (inhib == I_SQUOTE)
		prompt = ft_strdup("s_quote> ");
	else if (inhib == I_DQUOTE)
		prompt = ft_strdup("d_quote> ");
	else if (inhib == I_BSLASH)
		prompt = ft_strdup("bslash> ");
	else if (inhib == I_PIPE)
		prompt = ft_strdup("pipe> ");
	else if (inhib == I_DPIPE)
		prompt = ft_strdup("d_pipe> ");
	else if (inhib == I_DAND)
		prompt = ft_strdup("d_and> ");
	else
		prompt = ft_strdup("> ");
	ft_putstr(prompt);
	//ft_read_command_newline(line);
	ft_read_line(line, ft_strlen(prompt));
	ft_strdel(&prompt);
}

/*
** ft_inhibitor :
** Vérifie les fermetures de doubles et simples quotes, et des back-slashs.
** Vérifie si les pipes, double and et double pipe possèdent une deuxième
** commande simple après l'opérateur de contrôle.
** Rend la main à l'utilisateur si nécessaire => vérifie donc à chaque fois les
** erreurs de syntaxe, et split la chaine de char récupérée dans les bons
** maillons.
*/

/*int		ft_inhibitor(t_lexeme **lex)
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
}*/

int		ft_inhibitor(t_lexeme **lex, t_shell *shell)
{
	char	*tokenerror;
	char	*line;
	int		ret_inhib;

	if (!lex || !(*lex))
		//return (0);
		return (-1);
	line = NULL;
	while ((ret_inhib = ft_check_all_inhib(*lex)) != I_OK)
	{
		ft_read_line_again(ret_inhib, &line);
		if (ret_inhib == I_SQUOTE)
			ft_add_endoftoken_quote(*lex, &line, 39);
		else if (ret_inhib == I_DQUOTE)
			ft_add_endoftoken_quote(*lex, &line, 34);
		else if (ret_inhib == I_BSLASH)
			ft_add_endoftoken_bslash(*lex, &line);
		ft_lexer(lex, line);
		ft_lexlst_remove_if(lex, "", 0);
		if ((tokenerror = ft_check_tokenerror(*lex)) != NULL)
		{
			ft_puterr_unexp_token(tokenerror, shell->name);
			free(line);
			return (-1);
		}
	}
	free(line);
	return (0);
}
