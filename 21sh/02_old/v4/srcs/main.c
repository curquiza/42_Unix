/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:44:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/26 10:25:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_read_command_newline(char **line)
{
	char	*tmp;

	//tmp = *line;
	ft_strdel(line);
	if (get_next_line(0, line) != 1)
	{
		*line = ft_strjoin(NULL, "\n");
		return ;
	}
	//free(tmp);
	tmp = *line;
	*line = ft_strjoin(tmp, "\n");
	free(tmp);
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

	/*int		fd;
	int		pid;

	(void)ac;
	(void)av;
	(void)environ;
	
	pid = fork();
	if (pid == 0)
	{
		fd = open("file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(1, 2);
		dup2(fd, 1);
		write(1, "TEST\n", 5);
		write(2, "TEST sortie 2", 13);
		exit(0);
	}
	else if (pid > 0)
		wait(NULL);*/


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
