/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:56:25 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:58:25 by curquiza         ###   ########.fr       */
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
# include "expansion.h"
# include "semantics.h"
# include "execution.h"
# include "built_in.h"

# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>


/*
** init_shell.c
*/

t_shell		*ft_init_shell(char **environ);
char		**ft_init_priv(void);
char		**ft_init_env(char **environ);

/*
** var_tab.c
*/

char		*ft_get_varvalue(char **vartab, char *varname);
int			ft_get_varindex(char **vartab, char *varname);
int			ft_exist_in(char **vartab, char *varname);
//char		**ft_add_var(char ***env, char *newvar, char *value);
void		ft_add_var(char ***vartab, char *newvar, char *value);
void		ft_chg_varval(char **vartab, char *newvar, char *value);
void		ft_chg_varval_or_add(char ***vartab, char *newvar, char *value);

/*
** debug_display.c
*/

void		ft_put_semantics(t_ast *ast);
void		ft_put_redir2(t_redir *lst);
void		ft_put_lexlst_word(t_lexeme *lst);
void		ft_put_lexlst(t_lexeme *lst);
void		ft_putast(t_ast *ast, int step, int move);
void		ft_putast_2(t_ast *ast);

/*
** main.c
*/

void		ft_read_command_newline(char **line);

#endif
