/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:18:42 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/15 18:27:14 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

enum e_builtin	ft_is_built_in(char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (ECHO);
	if (!ft_strcmp(s, "cd"))
		return (CD);
	if (!ft_strcmp(s, "env"))
		return (ENV);
	if (!ft_strcmp(s, "setenv"))
		return (SETENV);
	if (!ft_strcmp(s, "unsetenv"))
		return (UNSETENV);
	if (!ft_strcmp(s, "exit"))
		return (EXIT);
	return (NOT_BUILTIN);
}

int				ft_exec_built_in(t_ast *ast, enum e_builtin ret, t_var *vartab)
{
	if (ret == ECHO)
		return (ft_builtin_echo(ast));
	if (ret == CD)
		return (ft_builtin_cd(ast, vartab));
	if (ret == ENV)
		return (ft_builtin_env(ast, vartab));
	if (ret == SETENV)
		return (ft_builtin_setenv(ast, vartab));
	if (ret == UNSETENV)
		return (ft_builtin_unsetenv(ast, vartab));
	if (ret == EXIT)
		return (ft_builtin_exit(ast));
	return (0);
}

int				ft_builtin_echo(t_ast *ast)
{
	(void)ast;
	ft_putendl("do echo");
	return (0);
}

int				ft_builtin_cd(t_ast *ast, t_var *vartab)
{
	(void)ast;
	(void)vartab;
	ft_putendl("do cd");
	return (0);
}

int				ft_builtin_env(t_ast *ast, t_var *vartab)
{
	(void)ast;
	(void)vartab;
	ft_putendl("do env");
	return (0);
}

int				ft_builtin_setenv(t_ast *ast, t_var *vartab)
{
	(void)ast;
	(void)vartab;
	ft_putendl("do setenv");
	return (0);
}

int				ft_builtin_unsetenv(t_ast *ast, t_var *vartab)
{
	(void)ast;
	(void)vartab;
	ft_putendl("do unsetenv");
	return (0);
}

int				ft_builtin_exit(t_ast *ast)
{
	if (ast->argtab && ft_tablen(ast->argtab) == 1)
		exit(1);
	if (ast->argtab && ft_tablen(ast->argtab) > 2)
	{
		ft_put_errmsg("21sh", ast->argtab[0], "too many arguments");
		return (1);
	}
	while (1);
	// gerer les arguments en char
	exit(atoi(ast->argtab[1]));
}
