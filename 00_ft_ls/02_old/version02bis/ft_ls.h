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
** Structures
*/

typedef struct	s_filestat
{
	char		*name;
	int			size;
	int			link;
	char		*typeoffile;
	char		*access;
	char		*user;
	char		*grp;
	int			sec_modiftime;
	int			nsec_modiftime;
	char		*str_modiftime;
	struct stat	structstat;

}				t_filestat;

/*
** Fichier option.c
*/

void	ft_init_opt(char *opt);
int		ft_parse_optarg(char *opt, char *s);
int		ft_fill_opt(char *opt, int ac, char **av);

/*
** Fichier filestat.c
*/

t_filestat *ft_new_filestat(char *filename);

#endif
