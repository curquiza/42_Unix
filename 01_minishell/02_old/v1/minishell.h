/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:20:38 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/03 12:33:18 by curquiza         ###   ########.fr       */
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

# define PROMPT "curquiza's shell $> "

/*
** Structures
*/

typedef struct	s_command
{
	char	*bin;
	char	**arg;
	//char	**env;
}				t_command;

/*
** Fucntions
*/

int				ft_isblank(char *s);
void			ft_tabdel(char ***tab);

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

char			**ft_get_path(char **env);
#endif
