/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:56:52 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/03 19:24:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h> //opendir, readdir, closedir
# include <sys/stat.h> //stat, lstat
# include <time.h> //time, ctime
# include <pwd.h> //getpwuid
# include <grp.h> //getgrgid
# include <errno.h> //perror, strerror
# include <sys/xattr.h> //getxattr, listxattr

/*
** Structure s_path
*/

typedef struct		s_path
{
	char			*name;
	struct stat		stat;
	char			*display;
	t_list			*lst_in;
	struct s_path	**inside;
	int				used;
}					t_path;

/*
** Fichier option.c
*/

void				ft_init_opt(char *opt);
int					ft_parse_optarg(char *opt, char *s);
int					ft_fill_opt(char *opt, int ac, char **av);

/*
** Fichier create_structpath.c
*/

t_list				*ft_get_lst_in(char *path);
void				ft_init_structpath(char *path, t_path *new);
t_path				*ft_new_structpath(char *path);

/*
** Fichier functions.c
*/

char				*ft_strjoin3(char *s1, char *s2, char *s3);
void				ft_sortascii_pathtab(t_path **tab);
void				ft_del_lst_in(t_list **alist);
void				ft_del_pathtab(t_path ***tab);

/*
** main.c
*/

void				ft_printtab_structpath(t_path **tab);

#endif
