/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:18:42 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:55:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

enum e_builtin	ft_is_built_in(char *s)
{
	if (s)
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
		if (!ft_strcmp(s, "set"))
			return (SET);
		if (!ft_strcmp(s, "unset"))
			return (UNSET);
		if (!ft_strcmp(s, "export"))
			return (EXPORT);
	}
	return (NOT_BUILTIN);
}

int				ft_exec_built_in(t_ast *ast, enum e_builtin ret)
{
	if (ret == ECHO)
		return (ft_builtin_echo(ast));
	if (ret == CD)
		return (ft_builtin_cd(ast));
	if (ret == ENV)
		return (ft_builtin_env(ast));
	if (ret == SETENV)
		return (ft_builtin_setenv(ast));
	if (ret == UNSETENV)
		return (ft_builtin_unsetenv(ast));
	if (ret == EXIT)
		return (ft_builtin_exit(ast));
	if (ret == SET)
		return (ft_builtin_set(ast));
	if (ret == UNSET)
		return (ft_builtin_unset(ast));
	if (ret == EXPORT)
		return (ft_builtin_export(ast));
	return (0);
}

int				ft_builtin_echo(t_ast *ast)
{
	int		i;
	int		nbr_arg;

	if (ast->argtab && (nbr_arg = ft_tablen(ast->argtab)) >= 2)
	{
		i = 1;
		while (ast->argtab[i])
		{
			ft_putstr(ast->argtab[i]);
			if (i != nbr_arg - 1)
				ft_putchar(' ');
			i++;
		}
	}
	ft_putchar('\n');
	return (CMD_SUCCESS);
}

int				ft_builtin_cd(t_ast *ast)
{
	(void)ast;
	ft_putendl("do cd");
	return (CMD_SUCCESS);
}

int				ft_builtin_env(t_ast *ast)
{
	ft_puttab(ast->shell->var_env);
	ast->left->left->left = NULL;
	return (CMD_SUCCESS);
}

int				ft_builtin_setenv(t_ast *ast)
{
	(void)ast;
	ft_putendl("do setenv");
	return (CMD_SUCCESS);
}

int				ft_builtin_unsetenv(t_ast *ast)
{
	(void)ast;
	ft_putendl("do unsetenv");
	return (CMD_SUCCESS);
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
	//while (1);
	// gerer les arguments en char
	exit(atoi(ast->argtab[1]));
}

int				ft_builtin_set(t_ast *ast)
{
	int		nbr_arg;

	nbr_arg = ft_tablen(ast->argtab);
	if (nbr_arg >= 2 && !ft_strcmp(ast->argtab[1], "-p"))
		ft_puttab(ast->shell->var_priv);
	else if (nbr_arg >= 2 && !ft_strcmp(ast->argtab[1], "-l"))
		ft_puttab(ast->shell->var_loc);
	else if (nbr_arg >= 2 && !ft_strcmp(ast->argtab[1], "-e"))
		ft_puttab(ast->shell->var_env);
	else if (nbr_arg >= 2 && !ft_strcmp(ast->argtab[1], "-A"))
	{
		ft_puttab(ast->shell->var_env);
		ft_puttab(ast->shell->var_loc);
		ft_puttab(ast->shell->var_priv);
	}
	else
	{
		ft_puttab(ast->shell->var_env);
		ft_puttab(ast->shell->var_loc);
	}
	return (0);
}

int				ft_builtin_unset(t_ast *ast)
{
	(void)ast;
	ft_putendl("do unset");
	return (CMD_SUCCESS);
}

int				ft_builtin_export(t_ast *ast)
{
	(void)ast;
	ft_putendl("do export");
	return (CMD_SUCCESS);
}
