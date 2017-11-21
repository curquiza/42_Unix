/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 15:14:35 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/13 17:30:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_is_separator :
** Check si le char est un séparateur de token.
*/

int		ft_is_separator(char c)
{
	//if (c == ' ' || c == '\n' || c == '\t')
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

/*
** ft_next_squote :
** Renvoie l'index de la chaine de char *s qui contient la prochaine simple
** quote ou l'index de la fin de la chaine ('\0') s'il n'y en a pas.
*/

int		ft_next_squote(int i, char *s)
{
	i++;
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}

/*
** ft_next_dquote :
** Renvoie l'index de la chaine de char *s qui contient la prochaine double
** quote ou l'index de la fin de la chaine ('\0') s'il n'y en a pas.
*/

int		ft_next_dquote(int i, char *s)
{
	i++;
	while (s[i] && s[i] != 34)
	{
		if (s[i] == 92 && s[i + 1])
			i = i + 2;
		else
			i++;
	}
	return (i);
}

/*
** ft_find_endoftoken :
** Renvoie l'index de la chaine de char *s correspondant à la fin du token.
*/

int		ft_find_endoftoken(int i, char *s)
{
	while (s[i] && s[i] != '\n' && !ft_is_separator(s[i]) && !ft_is_op(s + i))
	{
		if (s[i] == 92)
			i++;
		else if (s[i] == 39)
			i = ft_next_squote(i, s);
		else if (s[i] == 34)
			i = ft_next_dquote(i, s);
		if (s[i])
			i++;
	}
	return (i);
}

//void	ft_split_in_token()

/*
** ft_lexer :
** Split en token la chaine de char *s dans une liste chainée de type t_lexeme.
** Identifie aussi le type de token.
*/

void	ft_lexer(t_lexeme **lex, char *s)
{
	int			i;
	char		*token;
	int			ind_ionbr;
	int			ind_assword;
	t_lexeme	*last;

	ind_assword = 0;
	while (*s)
	{
		while (ft_is_separator(*s) == 1)
			s++;
		ind_ionbr = 0;
		i = 0;
		if (s[i] == '\n')
		{
			while (s[i] == '\n')
				i++;
		}
		else if (ft_isdigit(*s) == 1)
		{
			while (ft_isdigit(s[i]) == 1)
				i++;
			if (ft_is_redop(s + i) >= 1)
				ind_ionbr = 1;
			else
				i = ft_find_endoftoken(i, s);
		}
		else if ((i = ft_is_op(s)))
			;
		else if (*s == '-')
		{
			last = ft_lexlst_last(*lex);
			if (last && (last->op == GREATAND || last->op == LESSAND))
				i = 1;
			else
				i = ft_find_endoftoken(i, s);
		}
		else
			i = ft_find_endoftoken(i, s);
		if (i != 0)
		{
			token = ft_strsub(s, 0, i);
			last = ft_lexlst_new(token);
			ft_token_type(last, ind_ionbr, &ind_assword);
			ft_lexlst_addback(lex, last);
			ft_strdel(&token);
		}
		s = s + i;
	}
}
