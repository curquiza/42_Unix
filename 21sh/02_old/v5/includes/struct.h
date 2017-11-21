/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:28:05 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:00:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "token.h"

typedef struct		s_shell
{
	int		run;
	int		exit_status;
	char	**var_loc;
	char	**var_env;
	char	**var_priv;
}					t_shell;

typedef struct		s_lexeme
{
	char			*s;
	char			*hdoc;
	enum e_token	token;
	enum e_op		op;
	struct s_lexeme	*next;
}					t_lexeme;

typedef struct		s_redir
{
	enum e_op		op;
	int				io_nbr;
	char			*output;
	char			*hdoc;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_ast
{
	t_lexeme		*lex;
	t_lexeme		*ass_word;
	t_lexeme		*redir;
	t_lexeme		*cmd;
	char			**argtab;
	t_redir			*redir_list;
	struct s_shell	*shell;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
