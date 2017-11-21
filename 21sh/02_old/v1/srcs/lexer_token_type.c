/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 11:18:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/26 11:23:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_check_c_op(t_lexeme *lex)
{
	if (lex->token != 0)
		return ;
	lex->token = CTRL_OP;
	if (ft_strcmp(lex->s, ";") == 0)
		lex->op = SEMIC;
	else if (ft_strcmp(lex->s, "|") == 0)
		lex->op = PIPE;
	else if (ft_strcmp(lex->s, ";;") == 0)
		lex->op = DSEMIC;
	else if (ft_strcmp(lex->s, "||") == 0)
		lex->op = DPIPE;
	else if (ft_strcmp(lex->s, "&") == 0)
		lex->op = AND;
	else if (ft_strcmp(lex->s, "&&") == 0)
		lex->op = DAND;
	else
		lex->token = 0;
}

void	ft_check_r_op(t_lexeme *lex)
{
	if (lex->token != 0)
		return ;
	lex->token = RED_OP;
	if (!ft_strcmp(lex->s, "<<-")) // non géré
		lex->op = DLESSDASH;
	else if (!ft_strcmp(lex->s, "<<"))
		lex->op = DLESS;
	else if (!ft_strcmp(lex->s, ">>"))
		lex->op = DGREAT;
	else if (!ft_strcmp(lex->s, ">&"))
		lex->op = GREATAND;
	else if (!ft_strcmp(lex->s, "<&"))
		lex->op = LESSAND;
	else if (!ft_strcmp(lex->s, "<>")) // non géré
		lex->op = LESSGREAT;
	else if (!ft_strcmp(lex->s, ">|")) // non géré
		lex->op = CLOBBER;
	else if (!ft_strcmp(lex->s, "<"))
		lex->op = LESS;
	else if (!ft_strcmp(lex->s, ">"))
		lex->op = GREAT;
	else
		lex->token = 0;
}

void	ft_check_name(t_lexeme *lex)
{
	int		i;

	if (lex->token != 0)
		return ;
	i = 0;
	if (ft_isdigit(lex->s[i]))
		return ;
	while (lex->s[i])
	{
		if (lex->s[i] != '_' && ft_isalpha(lex->s[i]) == 0)
			return ;
		i++;
	}
	lex->token = NAME;
}

int			ft_is_op(char *s)
{
	if (!ft_strncmp(s, "<<-", 3))
		return (3);
	if (!ft_strncmp(s, ";;", 2) || !ft_strncmp(s, ">>", 2)
		|| !ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">&", 2)
		|| !ft_strncmp(s, "<&", 2) || !ft_strncmp(s, "||", 2)
		|| !ft_strncmp(s, "&&", 2) || !ft_strncmp(s, "<>", 2)
		|| !ft_strncmp(s, ">|", 2))
		return (2);
	else if (*s == '|' || *s == ';' || *s == '>' || *s == '<' || *s == '&')
		return (1);
	else
		return (0);
}

int		ft_is_redop_ionbr(char *s)
{
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2)
		|| !ft_strncmp(s, "<&", 2) || !ft_strncmp(s, ">&", 2))
		return (2);
	else if (*s == '>' || *s == '<')
		return (1);
	else
		return (0);
}
