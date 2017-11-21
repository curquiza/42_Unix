/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 22:12:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/26 13:52:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_del_ast :
** Supprime la totalité de l'arbre.
*/

void	ft_del_ast(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left)
			ft_del_ast(&(*ast)->left);
		if ((*ast)->right)
			ft_del_ast(&(*ast)->right);
		ft_lexlstdel(&((*ast)->ass_word));
		ft_lexlstdel(&((*ast)->redir));
		ft_lexlstdel(&((*ast)->cmd));
		ft_lexlstdel(&((*ast)->lex));
		ft_tabdel(&(*ast)->argtab);
		ft_redirlst_del(&(*ast)->redir_list);
		(*ast)->left = NULL;
		(*ast)->right = NULL;
		free(*ast);
		*ast = NULL;
	}
}

/*
** ft_is_in_lexlst :
** Vérifie si un type d'opérateur est présent dans la liste chainée de type
** t_lexeme.
*/

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

/*
** ft_ast_newnode :
** Malloc un nouveau maillon de l'arbre.
*/

t_ast	*ft_ast_newnode(t_lexeme *lex)
{
	t_ast	*new;

	if (!(new = (t_ast *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	new->lex = lex;
	new->ass_word = NULL;
	new->cmd = NULL;
	new->redir = NULL;
	new->argtab = NULL;
	new->redir_list = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/*
** ft_split_in_tree :
** Split la liste chainée lex par rapoort à l'opérateur de contrôle op.
** Le noeud : op.
** La branche gauche : la partie de lex à gauche de op.
** La branche droite : la partie de lex à droite de op.
*/

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
	ast->left = ft_ast_newnode(scmd_start);
	current = node->next;
	node->next = NULL;
	ast->lex = node;
	ast->right = ft_ast_newnode(current);
}

/*
** ft_build_ast :
** Parcourt l'arbre puis appelle la fonction de split.
*/

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

/*
** ft_ast :
** Fonction générale de construction de l'ast.
** A partir de la liste chainée lex, va construire une premiere fois l'arbre par
** rapport aux ';' puis va repasser dans l'arbre pour le re-spliter en se basant
** sur les '|' cette fois-ci.
*/

void	ft_ast(t_lexeme *lex, t_ast **ast)
{
	*ast = ft_ast_newnode(lex);
	ft_build_ast(*ast, SEMIC);
	ft_build_ast(*ast, PIPE);
}
