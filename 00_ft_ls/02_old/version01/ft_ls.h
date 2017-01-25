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

/*
** Fichier option.c
*/

void	ft_init_opt(char *opt);
int		ft_parse_optarg(char *opt, char *s);
int		ft_fill_opt(char *opt, int ac, char **av);

#endif
