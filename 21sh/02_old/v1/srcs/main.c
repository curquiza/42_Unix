/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:44:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/03 10:53:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:54:52 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/02 16:44:39 by curquiza         ###   ########.fr       */
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
	size_t		i;

	while (lst)
	{
		ft_putstr("s = \"");
		ft_putstr(lst->s);
		ft_putendl("\"");
		if (lst->esc && lst->token != NEWLINE)
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
		}
		ft_putstr("token = ");
		ft_putnbr_endl(lst->token);
		ft_putstr("op = ");
		ft_putnbr_endl(lst->op);
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
		ft_putnbr_endl( step);
		ft_put_lexlst_word(ast->lex);
		ft_putendl("");
		if (ast->right)
			ft_putast(ast->right, step, 2);
	}
}

int		main(int ac, char **av, char **environ)
{
	t_lexeme	*lex;
	t_ast		*ast;
	char		**env;
	char		*line;

	(void)ac;
	(void)av;
	env = ft_tabdup(environ);
	ft_init_env(&env);
	
	while (1)
	{
		lex = NULL;
		ast = NULL;
		ft_putstr_col("21sh> ", GREEN, DEF);
		ft_read_command_newline(&line);
		ft_lexer(&lex, line);
		if (ft_parser(&lex, &ast) == 0)
		{
			//ft_putstr("\nline = ");
			//ft_putendl(line);
			ft_put_lexlst(lex);
			ft_putast(ast, 0, 0);
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
