/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:33:31 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/15 18:12:44 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

enum	e_builtin
{
	NOT_BUILTIN = 0,
	ECHO = 1,
	CD = 2,
	ENV = 3,
	SETENV = 4,
	UNSETENV = 5,
	EXIT = 6
};

/*
** built_in.c
*/

int				ft_exec_built_in(t_ast *ast, enum e_builtin ret, t_var *vartab);
enum e_builtin	ft_is_built_in(char *s);


int				ft_builtin_echo(t_ast *ast);
int				ft_builtin_cd(t_ast *ast, t_var *vartab);
int				ft_builtin_env(t_ast *ast, t_var *vartab);
int				ft_builtin_setenv(t_ast *ast, t_var *vartab);
int				ft_builtin_unsetenv(t_ast *ast, t_var *vartab);
int				ft_builtin_exit(t_ast *ast);

# endif
