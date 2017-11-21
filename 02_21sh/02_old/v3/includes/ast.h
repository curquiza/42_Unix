/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 22:13:49 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/29 22:15:24 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token.h"
# include "struct.h"

/*
** ast.c
*/

void	ft_del_ast(t_ast **ast);
int		ft_is_in_lexlst(t_lexeme *lex, enum e_op op);
t_ast	*ft_ast_newnode(t_lexeme *lex);
void	ft_split_in_tree(t_ast *ast, enum e_op op);
void	ft_build_ast(t_ast *ast, enum e_op op);
void	ft_ast(t_lexeme *lex, t_ast **ast);

#endif
