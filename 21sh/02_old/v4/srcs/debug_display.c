/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 09:42:07 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/26 13:51:01 by curquiza         ###   ########.fr       */
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

void	ft_put_lexlst_word(t_lexeme *lst)
{
	if (!lst)
		ft_putendl("NULL");
	while (lst)
	{
		ft_putendl(lst->s);
		lst = lst->next;
	}
}

void	ft_put_lexlst(t_lexeme *lst)
{
//	size_t		i;

	while (lst)
	{
		ft_putstr("s = \"");
		ft_putstr(lst->s);
		ft_putendl("\"");
		/*if (lst->esc && lst->token != NEWLINE)
		{
			ft_putstr("     ");
			i = 0;
			while (i < ft_strlen(lst->s))
			{
				if (!lst->esc[i])
					ft_putchar('0');
				else
					ft_putchar('1');
				i++;
			}
			ft_putendl("");
		}*/
		ft_putstr("token = ");
		if (lst->token == NEWLINE)
			ft_putendl("NEWLINE");
		else if (lst->token == WORD)
			ft_putendl("WORD");
		else if (lst->token == ASS_WORD)
			ft_putendl("ASS_WORD");
		else if (lst->token == CTRL_OP)
			ft_putendl("CTRL_OP");
		else if (lst->token == RED_OP)
			ft_putendl("RED_OP");
		else if (lst->token == IO_NBR)
			ft_putendl("IO_NBR");
		//else if (lst->token == HDOC_DELIM)
		//	ft_putendl("HDOC_DELIM");
		if (lst->hdoc)
		{
			ft_putendl("hdoc = ");
			ft_putstr(lst->hdoc);
		}
		if (lst->op)
			ft_putnbr2("op = ", lst->op);
		ft_putendl("");
		lst = lst->next;
	}
}

void	ft_putast(t_ast *ast, int step, int move)
{
	if (ast)
	{
		step++;
		if (ast->left)
			ft_putast(ast->left, step, 1);
		if (move == 1)
			ft_putstr("L - ");
		else if (move == 2)
			ft_putstr("R - ");
		else
			ft_putstr("M - ");
		ft_putnbr_endl(step);
		ft_put_lexlst_word(ast->lex);
		ft_putendl("");
		if (ast->right)
			ft_putast(ast->right, step, 2);
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
	
	ft_putnbr2("leaf = ", leaf = ft_get_leaf_nbr(ast));
	/*if (ast)
	{
		if (ast->left)
			ft_putast_2(ast->left);
		ft_put_lexlst_word(ast->lex);
		if (ast->right)
			ft_putast_2(ast->right);
	}*/
}
