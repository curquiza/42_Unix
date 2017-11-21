/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:33:31 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:56:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

enum	e_builtin
{
	NOT_BUILTIN ,
	ECHO,
	CD,
	ENV,
	SETENV,
	UNSETENV,
	EXIT,
	SET,
	UNSET,
	EXPORT
};

/*
** built_in.c
*/

int				ft_exec_built_in(t_ast *ast, enum e_builtin ret);
enum e_builtin	ft_is_built_in(char *s);


int				ft_builtin_echo(t_ast *ast);
int				ft_builtin_cd(t_ast *ast);
int				ft_builtin_env(t_ast *ast);
int				ft_builtin_setenv(t_ast *ast);
int				ft_builtin_unsetenv(t_ast *ast);
int				ft_builtin_exit(t_ast *ast);
int				ft_builtin_set(t_ast *ast);
int				ft_builtin_unset(t_ast *ast);
int				ft_builtin_export(t_ast *ast);

# endif
