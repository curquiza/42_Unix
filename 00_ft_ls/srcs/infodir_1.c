/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infodir_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:16:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/20 18:49:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** Les fonctions de ce fichier remplissent le champs display avec les
** informations récupérées sur le file
*/

void			ft_type(t_path *tab)
{
	if (S_ISREG(tab->lstat.st_mode))
		tab->display[0] = '-';
	if (S_ISDIR(tab->lstat.st_mode))
		tab->display[0] = 'd';
	if (S_ISLNK(tab->lstat.st_mode))
		tab->display[0] = 'l';
	if (S_ISBLK(tab->lstat.st_mode))
		tab->display[0] = 'b';
	if (S_ISCHR(tab->lstat.st_mode))
		tab->display[0] = 'c';
	if (S_ISSOCK(tab->lstat.st_mode))
		tab->display[0] = 's';
	if (S_ISFIFO(tab->lstat.st_mode))
		tab->display[0] = 'p';
}

void			ft_access(t_path *tab)
{
	tab->display[1] = ((tab->lstat.st_mode & S_IRUSR) == S_IRUSR) ? 'r' : '-';
	tab->display[2] = ((tab->lstat.st_mode & S_IWUSR) == S_IWUSR) ? 'w' : '-';
	tab->display[3] = ((tab->lstat.st_mode & S_IXUSR) == S_IXUSR) ? 'x' : '-';
	tab->display[4] = ((tab->lstat.st_mode & S_IRGRP) == S_IRGRP) ? 'r' : '-';
	tab->display[5] = ((tab->lstat.st_mode & S_IWGRP) == S_IWGRP) ? 'w' : '-';
	tab->display[6] = ((tab->lstat.st_mode & S_IXGRP) == S_IXGRP) ? 'x' : '-';
	tab->display[7] = ((tab->lstat.st_mode & S_IROTH) == S_IROTH) ? 'r' : '-';
	tab->display[8] = ((tab->lstat.st_mode & S_IWOTH) == S_IWOTH) ? 'w' : '-';
	tab->display[9] = ((tab->lstat.st_mode & S_IXOTH) == S_IXOTH) ? 'x' : '-';
	if (tab->display[3] == '-' && ((tab->lstat.st_mode & S_ISUID) == S_ISUID))
		tab->display[3] = 'S';
	else if (tab->display[3] == 'x'
			&& ((tab->lstat.st_mode & S_ISUID) == S_ISUID))
		tab->display[3] = 's';
	if (tab->display[6] == '-' && ((tab->lstat.st_mode & S_ISGID) == S_ISGID))
		tab->display[6] = 'S';
	else if (tab->display[6] == 'x'
			&& ((tab->lstat.st_mode & S_ISGID) == S_ISGID))
		tab->display[6] = 's';
	if (tab->display[9] == '-' && ((tab->lstat.st_mode & S_ISVTX) == S_ISVTX))
		tab->display[9] = 'T';
	else if (tab->display[9] == 'x'
			&& ((tab->lstat.st_mode & S_ISVTX) == S_ISVTX))
		tab->display[9] = 't';
}

void			ft_uid_grp(t_path *tab, t_max_optl *max)
{
	int				i;
	//int				j;
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(tab->lstat.st_uid);
	i = 13 + max->link;
	ft_memmove(tab->display + i, pwd->pw_name, ft_strlen(pwd->pw_name));
	//j = 0;
	//while (j < (int)ft_strlen(pwd->pw_name))
	//{
	//	tab->display[i] = pwd->pw_name[j];
	//	i++;
	//	j++;
	//}
	grp = getgrgid(tab->lstat.st_gid);
	i = 15 + max->link + max->uid;
	ft_memmove(tab->display + i, grp->gr_name, ft_strlen(grp->gr_name));
	//j = 0;
	//while (j < (int)ft_strlen(grp->gr_name))
	//{
	//	tab->display[i] = grp->gr_name[j];
	//	i++;
	//	j++;
	//}
}

void			ft_size_majmin(t_path *tab, t_max_optl *max)
{
	int		i;
	int		maj;
	int		min;

	if (S_ISBLK(tab->lstat.st_mode) || S_ISCHR(tab->lstat.st_mode))
	{
		i = 16 + max->link + max->uid + max->gp + max->size_majmin;
		maj = major(tab->lstat.st_rdev);
		min = minor(tab->lstat.st_rdev);
		ft_fill_nbr(tab->display + i, min);
		i = 16 + max->link + max->uid + max->gp + max->size_majmin - 4;
		tab->display[i] = ',';
		ft_fill_nbr(tab->display + i - 1, maj);
	}
	else
	{
		i = 16 + max->link + max->uid + max->gp + max->size_majmin;
		ft_fill_nbr(tab->display + i, tab->lstat.st_size);
	}
}

void			ft_date(t_path *tab, t_max_optl *max)
{
	int		i;
	int		j;
	char	*tmp_date;

	i = 18 + max->link + max->uid + max->gp + max->size_majmin;
	tmp_date = ctime(&tab->lstat.st_mtimespec.tv_sec);
	j = 4;
	while (j < 16)
	{
		tab->display[i] = tmp_date[j];
		i++;
		j++;
	}
	if ((time(NULL) - tab->lstat.st_mtimespec.tv_sec) > 15811200)
	{
		j = 19;
		i = i - 5;
		while (j < 24)
		{
			tab->display[i] = tmp_date[j];
			i++;
			j++;
		}
	}
}
