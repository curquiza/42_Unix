/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 22:12:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/29 22:13:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_del_ast(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left)
			ft_del_ast(&(*ast)->left);
		if ((*ast)->right)
			ft_del_ast(&(*ast)->right);
		ft_lexlstdel(&((*ast)->lex));
		(*ast)->left = NULL;
		(*ast)->right = NULL;
		free(*ast);
		*ast = NULL;
	}
}

int		ft_is_in_lexlst(t_lexeme *lex, enum e_op op)
{
	while (lex)
	{
		if (lex->op == op)
			return (1);
		lex = lex->next;
	}
	return (0);
}

t_ast	*ft_ast_newnode(t_lexeme **lex)
{
	t_ast	*new;

	if (!(new = (t_ast *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	new->lex = *lex;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	ft_split_in_tree(t_ast *ast, enum e_op op)
{
	t_lexeme	*scmd_start;
	t_lexeme	*node;
	t_lexeme	*current;

	current = ast->lex;
	if (!current || (current && !current->next))
		return ;
	scmd_start = current;
	while (current->next && current->next->op != op)
		current = current->next;
	node = current->next;
	current->next = NULL;
	ast->left = ft_ast_newnode(&scmd_start);
	current = node->next;
	node->next = NULL;
	ast->lex = node;
	ast->right = ft_ast_newnode(&current);
}

void	ft_build_ast(t_ast *ast, enum e_op op)
{
	if (ast)
	{
		if (ft_is_in_lexlst(ast->lex, op) == 1)
			ft_split_in_tree(ast, op);
		if (ast->left)
			ft_build_ast(ast->left, op);
		if (ast->right)
			ft_build_ast(ast->right, op);
	}
}

void	ft_ast(t_lexeme *lex, t_ast **ast)
{
	*ast = ft_ast_newnode(&lex);
	ft_build_ast(*ast, SEMIC);
	ft_build_ast(*ast, PIPE);
}
