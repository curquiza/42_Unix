/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_get_endoftoken.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:41:10 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/26 15:42:05 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_split_endoftoken(int i, t_lexeme *lex, char **line)
{
	char		*tmp;
	char		*old_token;
	t_lexeme	*last;

	tmp = ft_strsub(*line, 0, i);
	last = ft_lexlst_last(lex);
	old_token = last->s;
	last->s = ft_strjoin(old_token, tmp);
	ft_strdel(&old_token);
	ft_strdel(&tmp);
	tmp = *line;
	*line = ft_strdup(*line + i);
	ft_strdel(&tmp);
	tmp = lex->esc;
	lex->esc = ft_strnew(ft_strlen(lex->s));
	ft_strdel(&tmp);
}

void	ft_rm_bslash_newline(t_lexeme *lex)
{
	int		i;

	i = 0;
	while (lex->s[i])
	{
		if (lex->s[i] == 39)
			i = ft_next_squote(i, lex->s);
		else if (lex->s[i] == 92 && lex->s[i + 1] == '\n')
			ft_escape_char(lex, i, '\n');
		if (lex->s[i])
			i++;
	}
}

void	ft_add_endoftoken_bslash(t_lexeme *lex, char **line)
{
	int			i;
	t_lexeme	*last;

	ft_rm_bslash_newline(last = ft_lexlst_last(lex));
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n' && !ft_is_separator((*line)[i]))
	{
		if ((*line)[i] == 92)
			i++;
		if ((*line)[i])
			i++;
	}
	ft_split_endoftoken(i, lex, line);
	last->op = 0;
	last->token = 0;
	ft_check_c_op(last);
	ft_check_r_op(last);
//	ft_check_name(last);
}

void	ft_add_endoftoken_quote(t_lexeme *lex, char **line, int quote)
{
	int			i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == 92 && quote == 34)
			i++;
		else if ((*line)[i] == quote)
		{
			i++;
			break;
		}
		if ((*line)[i])
			i++;
	}
	i = ft_find_endoftoken(i, *line);
	ft_split_endoftoken(i, lex, line);
}
