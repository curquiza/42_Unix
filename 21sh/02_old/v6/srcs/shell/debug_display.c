/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 09:42:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/29 17:47:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_semantics(t_ast *ast)
{
	ft_putendl("- SEMANTICS --\n");
	ft_putendl("ASS_WORD :");
	ft_put_lexlst_word(ast->ass_word);
	ft_putendl("\nREDIR :");
	ft_put_lexlst_word(ast->redir);
	ft_putendl("\nCMD :");
	ft_put_lexlst_word(ast->cmd);
	//ft_putendl("\nLEX (= arg) :");
	//ft_put_lexlst_word(ast->lex);
	ft_putendl("\nARGTAB :");
	if (ast->argtab)
		ft_puttab(ast->argtab);
	else
		ft_putendl("NULL");
	ft_putendl("\nREDIR_LIST :");
	ft_put_redir2(ast->redir_list);
	ft_putendl("\n--------------\n");
}

void	ft_put_redir2(t_redir *lst)
{
	if (!lst)
		ft_putendl("NULL");
	while (lst)
	{
		ft_putnbr2("io_nbr = ", lst->io_nbr);
		ft_putnbr2("op = ", lst->op);
		if (lst->output)
			ft_putendl2_fd("output = ", lst->output, 1);
		else
			ft_putendl("output = NULL");
		lst = lst->next;
		if (lst)
			ft_putendl("~");
	}
}

int		ft_get_leaf_nbr(t_ast *ast)
{
	int		leaf;

	leaf = 0;
	if (ast)
	{
		if (ast->left && ast->left->lex)
			leaf = leaf + ft_get_leaf_nbr(ast->left);
		if (ast->right && ast->right->lex)
			leaf = leaf + ft_get_leaf_nbr(ast->right);
		if (!ast->left && !ast->right)
			leaf++;
		return (leaf);
	}
	return (0);
}

void	ft_putast_2(t_ast *ast)
{
	int		leaf;

	leaf = 0;
	if (ast)
		leaf = ft_get_leaf_nbr(ast->right);
	ft_putnbr2("leaf = ", leaf);
	/*if (ast)
	{
		if (ast->left)
			ft_putast_2(ast->left);
		ft_put_lexlst_word(ast->lex);
		if (ast->right)
			ft_putast_2(ast->right);
	}*/
}
