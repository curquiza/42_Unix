/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:20:38 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/17 16:09:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

/*
** Define
*/

# define PROMPT_PWD_COL B_YELLOW
# define PROMPT_USR_COL CYAN

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
** Prompt
*/

void			ft_putprompt(char **env);
void			ft_putprompt_signal(char *user);

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

void			ft_initenv(char ***env, char **environ);

char			**ft_get_path(char **env);
int				ft_noaccess(char *path);
int				ft_fileserr(char *path);
void			ft_comnotfound(char *bin);

int				ft_exist(char *varname, char **env);
int				ft_isempty(char *varname, char **env);
char			*ft_get_envvar(char *varname, char **env);

void			ft_change_envvar1(char **env, char *newvar);
void			ft_change_envvar2(char **env, char *varname, char *newvalue);
void			ft_change_env1(char ***env, char *newvar);
void			ft_change_env2(char ***env, char *varname, char *value);

/*
** Builtins
*/

void			ft_exit_if(char *bin, t_command **com);
int				ft_callbuiltin_if(t_command *com, char ***env);

void			ft_echo(char **arg);

void			ft_cd(char **arg, char ***env);

void			ft_env(char **arg, char **env);

char			**ft_setenv_newenv(char *newvar, char **env);
void			ft_setenv(char **arg, char ***env);

char			**ft_unsetenv_newenv(char *var, char **env);
void			ft_unsetenv(char **arg, char ***env);

/*
** Signals
*/

void			ft_ctrlc_prompt(int sig);
void			ft_ctrlc_noprompt(int sig);
void			ft_signal_ctrlc(char **env);
void			ft_ctrlc_donothing(int sig);
void			ft_signal_minishell(char *bin);

/*
** Minishell
*/

void			ft_childprocess(t_command *com, char **env);
void			ft_exec_allcom(t_command **com, char ***env);

#endif
