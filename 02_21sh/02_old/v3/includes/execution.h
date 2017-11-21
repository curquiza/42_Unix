/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:02:26 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/17 11:36:36 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

enum	e_cmd_search
{
	ISDIR = 1,
	NOSUCHFILE = 2,
	NOTFOUND = 3,
	NOPERM = 4,
	FOUND = 5
};

/*
** execution.c
*/

void	ft_apply_semic(t_ast *ast, t_var *vartab);
void	ft_apply_pipe(t_ast *ast, t_var *vartab);
void	ft_execution(t_ast *ast, t_var *vartab);

/*
** exec_error_msg.c
*/

void	ft_put_errmsg(char *bin, char *s, char *msg);
int		ft_putmsg_cmderr(char *cmd, enum e_cmd_search ret);

/*
** exec_simple_cmd.c
*/

int		ft_exec_simple_cmd(t_ast *ast, t_var *vartab);

#endif
