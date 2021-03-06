/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:56:25 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/02 13:06:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "struct.h"
# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "ast.h"

# include <fcntl.h>

/*
** env.c
*/

char		*ft_get_varvalue(char **env, char *varname);
int			ft_get_varindex(char **env, char *varname);
int			ft_exist_in_env(char **env, char *varname);
char		**ft_add_envvar(char ***env, char *newvar, char *value);
void		ft_change_envvar(char **env, char *newvar, char *value);
void		ft_modif_env(char ***env, char *newvar, char *value);
void		ft_init_env(char ***env);

/*
** main.c
*/

void		ft_put_lexlst_word(t_lexeme *lst);
void		ft_put_lexlst(t_lexeme *lst);
void		ft_putast(t_ast *ast, int step, int move);
void		ft_read_command_newline(char **line);

#endif
