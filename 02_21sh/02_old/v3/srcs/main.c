/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:44:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/16 18:10:09 by curquiza         ###   ########.fr       */
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
	ft_putendl("\nREDIR2 :");
	ft_put_redir2(ast->redir2);
	ft_putendl("\n--------------\n");
}

void	ft_put_redir2(t_redir *lst)
{
	if (!lst)
		ft_putendl("NULL");
	while (lst)
	{
		ft_putnbr2("io_nbr = ", lst->io_nbr);
		if (lst->op)
			ft_putendl2_fd("op = ", lst->op->s, 1);
		else
			ft_putendl("op = NULL");
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

/*
** DEROULEMENT DU SHELL :
**
** 1) lexer : on sépare la chaine de char envoyée par l'utilisateur en token
** (càd en mots) et on identifie le type de token, si possible.
** ex : opérateur de contrôle, io_number, word...
**
** 2) parser : on verifie les erreurs de syntax + on gere les inhibiteurs (le
** shell attend le retour de l'user) + on recupere les arguments des here-docs.
** Cf shell grammar pour les hdocs.
**
** 3) ast : on construit l'abstract syntax tree. Les noeuds sont des opérateurs
** de controle et les feuilles des commandes simples.
**
** 4) expansion : on gère les expansions, càd dans mon cas pour l'instant la
** parameter expansion (en mode bébé) et la removal quotes (simple quote,
** double quote et back-slash). Cf shell grammar.
**
** 5) semantic_analysis : dans l'ast, à l'intérieur de chaque feuille (= les
** commandes simples) on split les tokens en differents roles : assigment words,
** commande, arguments, ou redirection.
** Dans cette partie, pour faciliter la future execution, on crée un **char pour
** stocker les arguments, et on re-organise les redirections dans une liste
** chainée adaptée.
**
** 6) execution : on execute la totalité des commandes de l'ast.
*/

int		main(int ac, char **av, char **environ)
{
	t_lexeme	*lex;
	t_ast		*ast;
	t_var		*vartab;
	char		*line;

	(void)ac;
	(void)av;
	vartab = ft_init_vartab(environ);
	//ft_puttab(vartab->env);
	
	line = NULL;
	while (1)
	{
		lex = NULL;
		ast = NULL;
		ft_putstr_col("21sh> ", GREEN, DEF);
		ft_read_command_newline(&line);
		ft_lexer(&lex, line); // ETAPE 1
		if (ft_parser(&lex, vartab) == 0) // ETAPE 2
		{
			ft_ast(lex, &ast); // ETAPE 3
			ft_expansion(ast, vartab); // ETAPE 4

			ft_putendl("\n---- AST -----\n");
			ft_putast(ast, 0, 0);
			ft_putast_2(ast);
			ft_putendl("--------------\n");

			ft_semantic_analysis(ast); // ETAPE 5
			ft_execution(ast, vartab); // ETAPE 6
			ft_del_ast(&ast);
		}
		else
			ft_lexlstdel(&lex);
	}
	
	/*(void)ac;
	(void)av;
	(void)environ;
	int		pid;
	int		pfd[2];
	char	*argls[4] = {"ls", "titi", "Makefile", NULL};
	char	*argcat[3] = {"cat", "-e", NULL};

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execve("/bin/cat", argcat, NULL);
	}
	else if (pid > 0)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		execve("/bin/ls", argls, NULL);
	}*/

	/*(void)ac;
	(void)av;
	(void)environ;
	int		pid;
	int		pfd[2];
	char	*argls[4] = {"ls", "titi", "Makefile", NULL};
	char	*argcat[3] = {"cat", "-e", NULL};

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		execve("/bin/ls", argls, NULL);
	}
	else if (pid > 0)
	{
		wait(&pid);
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execve("/bin/cat", argcat, NULL);
	}*/

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
