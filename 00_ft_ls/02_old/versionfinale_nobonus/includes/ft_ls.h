/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:56:52 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/21 11:19:33 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

/*
** Couleurs
*/

# define DEF "\033[0m"
# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define RED_BOLD "\x1b[1;31m"
# define GREEN "\x1b[32m"
# define GREEN_BOLD "\x1b[1;32m"
# define YELLOW "\x1b[33m"
# define YELLOW_BOLD "\x1b[1;33m"
# define BLUE "\x1b[34m"
# define BLUE_BOLD "\x1b[1;34m"
# define PINK "\x1b[35m"
# define PINK_BOLD "\x1b[1;35m"
# define CYAN "\x1b[36m"
# define CYAN_BOLD "\x1b[1;36m"
# define WHITE "\x1b[37m"

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
** Structure s_max_optl
*/

typedef struct		s_max_optl
{
	int				size_majmin;
	int				link;
	int				uid;
	int				gp;
}					t_max_optl;

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
** fcttab.c
*/

void				ft_init_fcttab(void (**f)(t_path **, char *));
void				ft_run(t_path **argpath, char *opt,
							void (**f)(t_path **, char *));

/*
** functions.c
*/

char				*ft_strjoin3(char *s1, char *s2, char *s3);
int					ft_pathtablen(t_path **tab);
int					ft_toopen(t_path *path, char *opt, int is_start);
void				ft_fill_nbr(char *str, unsigned long long int value);
char				*ft_name_in_path(char *path);

/*
** sort_ascii.c
*/

void				ft_sortascii_pathtab(t_path **tab);
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

void				ft_opt_t(t_path **tab, char *opt);

/*
** opt_l.c
*/

void				ft_check_max(t_path *tab, t_max_optl *max);
t_max_optl			*ft_get_max(t_path **tab);
char				*ft_malloc_display(t_path *tab, t_max_optl *max);
void				ft_fill_display(t_path *tab, t_max_optl *max,
									char *tmp_display);
void				ft_opt_l(t_path **tab, char *opt);

/*
** infodir_1.c
*/

void				ft_type(t_path *tab);
void				ft_access(t_path *tab);
void				ft_uid_grp(t_path *tab, t_max_optl *max);
void				ft_size_majmin(t_path *tab, t_max_optl *max);
void				ft_date(t_path *tab, t_max_optl *max);

/*
** infodir_2.c
*/

char				*ft_get_link(char *name);
void				ft_acl_xatt(t_path *tab);
void				ft_name(t_path *tab, t_max_optl *max, char *tmp_display);

/*
** opt_r.c
*/

void				ft_swap_pathtab(t_path **tab, int i, int j);
void				ft_reverse_pathtab(t_path **tab);
void				ft_opt_r(t_path **tab, char *opt);

/*
** opt_bigr.c
*/

void				ft_sink(t_path **tab, char *opt,
							void (**f)(t_path **, char *), int pos);
void				ft_opt_bigr(t_path **argpath, char *opt,
								void (**f)(t_path **, char *));

/*
** display.c
*/

void				ft_print_notdir(t_path **argpath, char *opt);
void				ft_print_err(t_path *tab);
void				ft_print_dirpath(t_path *tab, int len);
int					ft_get_last(t_path **tab, char *opt);
void				ft_display(t_path **argpath, char *opt,
								void (**f)(t_path **, char *));

/*
** display_indir.c
*/

int					ft_isnotsrch(t_path *tab, char *opt, int is_start);
void				ft_print_innotsrch(t_path *tab, char *opt);
void				ft_print_total(t_path **tab);
void				ft_print_indir(t_path *tab, char *opt, int is_start);
void				ft_print(t_path *tab, char *opt);

/*
** colors.c
*/

void				ft_putstr_color(char *display, char *color);
void				ft_putendl_color(char *display, char *color);
void				ft_print_color(char *str, t_path *tab);

#endif
