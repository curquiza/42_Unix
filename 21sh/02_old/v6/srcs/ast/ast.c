/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 22:12:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/29 18:26:25 by curquiza         ###   ########.fr       */
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

t_ast	*ft_ast_newnode(t_lexeme *lex, t_shell *shell)
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
	new->shell = shell;
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

/*void	ft_split_in_tree(t_ast *ast, enum e_op op1, enum e_op op2)
{
	t_lexeme	*scmd_start;
	t_lexeme	*node;
	t_lexeme	*current;

	current = ast->lex;
	if (!current || (current && !current->next))
		return ;
	scmd_start = current;
	while (current->next && current->next->op != op1
						&& current->next->op != op2)
		current = current->next;
	node = current->next;
	current->next = NULL;
	if (scmd_start)
		ast->left = ft_ast_newnode(scmd_start, ast->shell);
	current = node->next;
	node->next = NULL;
	ast->lex = node;
	if (current)
		ast->right = ft_ast_newnode(current, ast->shell);
}*/

/*
** ft_build_ast :
** Parcourt l'arbre puis appelle la fonction de split.
** Deux opérateurs possible dans le cas de priorités égales (ex : || et &&)
*/

/*void	ft_build_ast(t_ast *ast, enum e_op op1, enum e_op op2)
{
	if (ast)
	{
		if (ft_is_in_lexlst(ast->lex, op1) || ft_is_in_lexlst(ast->lex, op2))
			ft_split_in_tree(ast, op1, op2);
		if (ast->left)
			ft_build_ast(ast->left, op1, op2);
		if (ast->right)
			ft_build_ast(ast->right, op1, op2);
	}
}*/

//void	ft_split_in_tree_dpipe_dand(t_ast *ast)
void	ft_split_in_tree(t_ast *ast, enum e_op op1, enum e_op op2)
{
	t_lexeme	*left_end;
	t_lexeme	*node;
	t_lexeme	*current;

	left_end = NULL;
	node = NULL;
	current = ast->lex;
	if (!current || (current && !current->next))
		return ;
	while (current && current->next)
	{
	//	if (current->next->op == DAND || current->next->op == DPIPE)
		if (current->next->op == op1 || current->next->op == op2)
		{
			node = current->next;
			left_end = current;
		}
		current = current->next;
	}
	ast->right = ft_ast_newnode(node->next, ast->shell);
	node ? node->next = NULL: 0;
	left_end ? left_end->next = NULL: 0;
	ast->left = ft_ast_newnode(ast->lex, ast->shell);
	ast->lex = node;
}

//void	ft_build_ast_dpipe_dand(t_ast *ast)
void	ft_build_ast(t_ast *ast, enum e_op op1, enum e_op op2)
{
	if (ast)
	{
		//if (ft_is_in_lexlst(ast->lex, DAND) || ft_is_in_lexlst(ast->lex, DPIPE))
		if (ft_is_in_lexlst(ast->lex, op1) || ft_is_in_lexlst(ast->lex, op2))
		//	ft_split_in_tree_dpipe_dand(ast);
			ft_split_in_tree(ast, op1, op2);
		if (ast->right)
		{
			ft_build_ast(ast->right, op1, op2);
			//ft_build_ast_dpipe_dand(ast->right);
		}
		if (ast->left)
			ft_build_ast(ast->left, op1, op2);
			//ft_build_ast_dpipe_dand(ast->left);
	}
}

/*
** ft_ast :
** Fonction générale de construction de l'ast.
** A partir de la liste chainée lex, va construire une premiere fois l'arbre par
** rapport aux ';' puis va repasser dans l'arbre pour reduire chaque noeud en
** commande simple par rapport aux autres opérateurs de contrôle.
** L'ordre de passage correspond à la priorité de chaque opérateur.
** Si le flag --ast est activé, affiche l'arbre.
*/

void	ft_ast(t_lexeme *lex, t_ast **ast, t_shell *shell)
{
	if (!ast)
		return ;
	*ast = NULL;
	if (lex)
	{
		*ast = ft_ast_newnode(lex, shell);
		ft_build_ast(*ast, SEMIC, -1);
		ft_build_ast(*ast, DAND, DPIPE);
		//ft_build_ast_dpipe_dand(*ast);
		ft_build_ast(*ast, PIPE, -1);
	}
	if (*ast && (*ast)->shell->flags->ast == 1)
		ft_putast(*ast);
}
