/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:44:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/06 18:05:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_lexlst_word(t_lexeme *lst)
{
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
		else if (lst->token == HDOC_DELIM)
			ft_putendl("HDOC_DELIM");
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

void	ft_read_command_newline(char **line)
{
	char	*tmp;

	tmp = *line;
	get_next_line(0, line);
	free(tmp);
	tmp = *line;
	*line = ft_strjoin(tmp, "\n");
	free(tmp);
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
		if (ast->lex)
			ft_put_lexlst_word(ast->lex);
		else
			ft_putendl("NULL");
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

int		main(int ac, char **av, char **environ)
{
	t_lexeme	*lex;
	t_ast		*ast;
	t_var		*tabvar;
	char		*line;

	(void)ac;
	(void)av;
	tabvar = ft_init_tabvar(environ);
	//ft_puttab(tabvar->env);
	
	line = NULL;
	while (1)
	{
		lex = NULL;
		ast = NULL;
		ft_putstr_col("21sh> ", GREEN, DEF);
		ft_read_command_newline(&line);
		ft_lexer(&lex, line); // ETAPE 1
		if (ft_parser(&lex, tabvar) == 0) // ETAPE 2
		{
			ft_ast(lex, &ast); // ETAPE 3
			ft_expansion(ast, tabvar); // ETAPE 4

			ft_putendl("\n---- AST -----\n");
			ft_putast(ast, 0, 0);
			ft_putast_2(ast);
			ft_putendl("--------------\n");

			ft_del_ast(&ast);
		}
		else
			ft_lexlstdel(&lex);
	}
	

/*	int		fd;
	int		ret;

	fd = open("FILE", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putnbr2("fd de FILE avant dup = ", fd);
	ft_putnbr2("ret dup2 = ", ret = dup2(fd, 1));
	ft_putnbr2("fd de FILE apres dup = ", fd);
	//ft_putnbr2("ret close = ", close(fd));
	ft_putendl_fd("coco sortie 1", 1);
	ft_putendl_fd("coco sortie 2", 2);
	ft_putnbr2("close = ", close(fd));
	ft_putnbr2("close = ", close(ret));
	ft_putnbr2("close = ", close(1));
	ft_putnbr2("close = ", close(fd));
	ft_putnbr2("ret de dup(1) =", ret = dup(ret));
	ft_putendl("~~~~~~~");
	//ft_putnbr2("ret dup2 = ", ret = dup2(1, fd));
	ft_putendl_fd("titi sortie 1", ret);
	ft_putendl_fd("titi sortie 2", 2);*/

/*	int ret;
	int	oldfd = 2;
	int	newfd = 1;
	ft_putnbr2("ret dup2 = ", ret = dup2(oldfd, newfd));
	ft_putendl_fd("coco2", 2);
	ft_putendl_fd("coco1", 1);
	close(oldfd);
	dup(1);
	ft_putendl_fd("toto2", 2);
	ft_putendl_fd("toto1", 1);*/
/*	ft_putnbr2("ret dup2 = ", dup2(1, 2));
	ft_putendl_fd("titi", 2);
	ft_putendl_fd("titi1", 1);*/

/*	int		pid;
	int		fd;
	int		fd2;
	int 	ret;
	pid = fork();
	if (pid == 0)
	{
		ft_putnbr_fd(ret = dup2(2, 1), 2);
		ft_putendl_fd("", 2);
		fd = open("FILE", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		ft_putnbr_fd(ret = dup2(fd, ret), 2);
		ft_putendl_fd("", 2);
		fd2 = open("FILE2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		ft_putnbr_fd(ret = dup2(fd2, ret), 2);
		ft_putendl_fd("", 2);
		ft_putendl_fd("toto sortie 1", 1);
		ft_putendl_fd("toto sortie 2", 2);
		exit(0);
	}
	else
		wait(&pid);
	//ft_putendl_fd("sortie 1", 1);
	//ft_putendl_fd("sortie 2", 2);*/

	return (0);
}
