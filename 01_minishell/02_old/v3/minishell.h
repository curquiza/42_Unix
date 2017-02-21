/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:20:38 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/05 15:14:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <sys/wait.h>

/*
** Global variables
*/

# define PROMPT "minishell $> "

/*
** Structures
*/

typedef struct	s_command
{
	char	*bin;
	char	**arg;
}				t_command;

/*
** Fucntions
*/

int				ft_isblank(char *s);
void			ft_comdel(t_command ***com);
int				ft_strisalnum(char *s);

/*
** Parsing
*/

int				ft_check_quote(char *line);
int				ft_check_line(char *line);

int				ft_countcom(char *s);
int				ft_comlen(char *s);
char			**ft_comsplit(char *s);

int				ft_arglen(char *s);
char			*ft_get_onearg(char *s);
int				ft_countarg(char *s);
char			**ft_add_arg(char *s, char *bin);

t_command		**ft_create_comtab(char **split, int size);
t_command		**ft_get_commands(char *line);

/*
** Env
*/

void			ft_init_shlvl(char **env);
char			**ft_get_path(char **env);
void			ft_change_envvar1(char **env, char *varname, char *newvalue);
void			ft_change_envvar2(char **env, char *newvar);

/*
** Builtins
*/

void			ft_echo(char **arg);
void			ft_env(char **arg, char **env);
void			ft_setenv(char **arg, char ***env);

#endif
