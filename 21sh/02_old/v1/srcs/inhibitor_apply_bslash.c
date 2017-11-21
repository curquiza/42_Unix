/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_apply_bslash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:36:53 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/26 15:38:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_escape_char(t_lexeme *lex, int i, char esc_char)
{
	char	*tmp;
	int		gap;
	int		len;

	if (esc_char == '\n')
		gap = 2;
	else
		gap = 1;
	len = ft_strlen(lex->s);
	tmp = lex->s;
	lex->s = ft_strnew(len - gap);
	ft_strncpy(lex->s, tmp, i);
	ft_strcpy(lex->s + i, tmp + i + gap);
	free(tmp);
	if (esc_char != '\n')
	{
		tmp = lex->esc;
		lex->esc = ft_strnew(ft_strlen(lex->s));
		ft_memcpy(lex->esc, tmp, i);
		lex->esc[i] = 1;
		ft_memcpy(lex->esc + i + 1, tmp + i + 2, len - (i + 2));
		free(tmp);
	}
}

void	ft_apply_bslash(t_lexeme *lex)
{
	int		i;

	while (lex)
	{
		//if (lex->token != NEWLINE) //laisser ?
		//{
			i = 0;
			while (lex->s[i])
			{
				if (lex->s[i] == 39)
					i = ft_next_squote(i, lex->s);
				else if (lex->s[i] == 34)
					i = ft_next_dquote(i, lex->s);
				else if (lex->s[i] == 92)
					ft_escape_char(lex, i, lex->s[i + 1]);
				if (lex->s[i])
					i++;	
			}
		//}
		lex = lex->next;
	}
}
