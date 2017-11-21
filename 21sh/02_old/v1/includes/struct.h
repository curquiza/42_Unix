/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:28:05 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/03 12:15:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "token.h"

typedef struct		s_hdoc
{
	char			*arg;
	struct s_hdoc	*next;
}					t_hdoc;

typedef struct		s_lexeme
{
	char			*s;
	char			*esc;
	enum e_token	token;
	enum e_op		op;
	struct s_hdoc	*hdoc;
	struct s_lexeme	*next;
}					t_lexeme;

typedef struct		s_ast
{
	t_lexeme		*lex;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
