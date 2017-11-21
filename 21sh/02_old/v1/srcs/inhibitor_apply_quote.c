/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_apply_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:33:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/26 16:44:35 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_rm_quote(t_lexeme *lex, int start, int i)
{
	char	*tmp;
	int		len;

	len = ft_strlen(lex->s);
	tmp = lex->s;
	lex->s = ft_strnew(len - 2);
	ft_strncpy(lex->s, tmp, start);
	ft_strncpy(lex->s + start, tmp + start + 1, i - start - 1);
	ft_strcpy(lex->s + i - 1, tmp + i + 1);
	free(tmp);
	tmp = lex->esc;
	lex->esc = ft_strnew(len - 2);
	ft_memcpy(lex->esc, tmp, start);
	ft_memcpy(lex->esc + start, tmp + start + 1, i - start - 1);
	ft_memcpy(lex->esc + i - 1, tmp + i + 1, len - i - 1);
	free(tmp);
}

int		ft_is_escchar_in_dquote(char c)
{
	if (c == '$' || c == '`' || c == 34 || c == 92 || c == '\n')
		return (1);
	return (0);
}

void	ft_apply_dquote(t_lexeme *lex, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while (lex->s[*i] && lex->s[*i] != 34)
	{
		if (lex->s[*i] == 92 && ft_is_escchar_in_dquote(lex->s[*i + 1]) == 1)
			ft_escape_char(lex, *i, lex->s[*i + 1]);
		(*i)++;
	}
	ft_rm_quote(lex, start, *i);
	(*i)--;
    // ici pour ajouter les autres changements faits ds les dquotes, cad le $ ?
	// ou faire le $ plus tard car aussi pour les char non entre dquote (mais
	// pas entre squote)
}

void	ft_apply_squote(t_lexeme *lex, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while (lex->s[*i]
			&& (lex->s[*i] != 39 || (lex->s[*i] == 39 && lex->esc[*i] == 1)))
		(*i)++;
	ft_rm_quote(lex, start, *i);
	// remplir lex->esc par des 2 pr les char entre simple quote 
	// (= intouchable par la suite)
	(*i)--;
}

void	ft_apply_quote(t_lexeme *lex)
{
	int		i;

	while (lex)
	{
		//if (lex->token != NEWLINE) // laisser ?
		//{
			i = 0;
			while (lex->s[i])
			{
				if (lex->s[i] == 39 && lex->esc[i] == 0)
					ft_apply_squote(lex, &i);
				else if (lex->s[i] == 34 && lex->esc[i] == 0)
					ft_apply_dquote(lex, &i);
				else
					i++;	
			}
		//}
		lex = lex->next;
	}
}

