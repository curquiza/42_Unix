/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:56:52 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/11 10:35:33 by curquiza         ###   ########.fr       */
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
	struct stat		lstat;
	char			*display;
	t_list			*lst_in;
	struct s_path	**inside;
	int				error;
}					t_path;

/*
** option.c
*/

void				ft_init_opt(char *opt);
int					ft_parse_optarg(char *opt, char *s);
int					ft_fill_opt(char *opt, int ac, char **av);

/*
** create_structpath.c
*/

t_list				*ft_get_lst_in(char *filename, char *opt);
t_path				*ft_new_structpath(char *filename, char *path, char *opt);
t_path				**ft_init_insidetab(int *cpt, t_list *lst_in);
t_path				**ft_new_inside(t_path *path, char *opt);

/*
** functions.c
*/

char				*ft_strjoin3(char *s1, char *s2, char *s3);
void				ft_sortascii_pathtab(t_path **tab);
void				ft_swap_pathtab(t_path **tab, int i, int j);
int					ft_pathtablen(t_path **tab);
int					ft_isdir(t_path *path);

/*
** start.c
*/

char				**ft_tab_path(int ac, char **av);
t_path				**ft_create_argpath(char **arg, char *opt);
void				ft_print_fileerror(t_path **argpath);
void				ft_start(int ac, char **av, t_path ***argpath, char *opt);

/*
** opt_t.c
*/

void				ft_sorttime_pathtab(t_path **tab);
void				ft_opt_t(t_path **tab, char *opt);

/*
** opt_r.c
*/

void				ft_reverse_pathtab(t_path **tab);
void				ft_opt_r(t_path **tab, char *opt);

/*
** opt_bigr.c
*/

void				ft_opt_bigr(t_path **argpath, char *opt,
												void (**f)(t_path **, char *));

/*
** fcttab.c
*/

void				ft_init_fcttab(void (**f)(t_path **, char *));
void				ft_run(t_path **argpath, char *opt,
												void (**f)(t_path **, char *));

/*
** display.c
*/

void				ft_print_notdir(t_path **argpath);
void				ft_print_indir(t_path *tab);
void				ft_print_dirpath(t_path *tab, int len);
void				ft_print_erracc(t_path *tab);
void				ft_display(t_path **argpath, char *opt,
												void (**f)(t_path **, char *));
/*
** del.c
*/

void				ft_del_lst_in(t_list **alst);
void				ft_del_pathtab(t_path ***tab);

/*
** main.c
*/

void				ft_print_pathtab(t_path **tab);

#endif
