/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:33:05 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/06 18:01:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

/*
** inhibitor.c
*/

int			ft_inhibitor(t_lexeme **lex);

/*
** inhibitor_check.c
*/

int			ft_check_quote(t_lexeme *lex);
int			ft_check_pipe(t_lexeme *lex);
int			ft_check_bslash(t_lexeme *lex);

/*
** inhibitor_get_endoftoken.c
*/

void		ft_split_endoftoken(int i, t_lexeme *lex, char **line);
void		ft_add_endoftoken_bslash(t_lexeme *lex, char **line);
void		ft_add_endoftoken_quote(t_lexeme *lex, char **line, int quote);
void		ft_rm_bslash_newline(char **s);

/*
** syntax_error.c
*/

void		ft_puterr_unexp_token(char *token);
t_lexeme	*ft_next_token(t_lexeme *lex);
char		*ft_check_tokenerror(t_lexeme *lex);

/*
** here_doc.c
*/

int			ft_is_quoted(char *s);
void		ft_get_hdoc_lines(t_lexeme *lex, int quoted);
void		ft_hdoc(t_lexeme *lex, t_var *tabvar);

/*
** inhibitor_apply_bslash.c
*/

//void		ft_escape_char(t_lexeme *lex, int i, char esc_char);
//void		ft_escape_char(char **s, int i, char esc_char);
//void		ft_apply_bslash(t_lexeme *lex); // plus utilisée pour l'instant

/*
** inhibitor_apply_quote.c
*/

//void		ft_rm_quote(t_lexeme *lex, int start, int i);
//void		ft_apply_dquote(t_lexeme *lex, int *i);
//void		ft_apply_squote(t_lexeme *lex, int *i);
//void		ft_apply_quote(t_lexeme *lex);

/*
** parser.c
*/

int			ft_parser(t_lexeme **lex, t_var *tabvar);

#endif

