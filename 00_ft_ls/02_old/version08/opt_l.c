/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:24:53 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/19 16:01:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

char			*ft_get_link(char *name)
{
	int		i;
	char	*buf_link;

	i = 1;
	if (!(buf_link = ft_strnew(i)))
		return (NULL);
	while (readlink(name, buf_link, i) == i)
	{
		ft_strdel(&buf_link);
		if (!(buf_link = ft_strnew(i)))
			return (NULL);
		i++;
	}
	return (buf_link);
}

t_max_optl		*ft_get_max(t_path **tab)
{
	t_max_optl		*max;
	struct group	*grp;
	struct passwd	*pwd;
	int				i;
	
	if (!(max = (t_max_optl *)malloc(sizeof(*max))))
		return (NULL);
	max->size_majmin = 0;
	max->uid = 0;
	max->gp = 0;
	max->link = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i]->display == NULL)
			i++;
		else
		{
			pwd = getpwuid(tab[i]->lstat.st_uid);
			grp = getgrgid(tab[i]->lstat.st_gid);
			if (ft_ullintlen(tab[i]->lstat.st_nlink) > max->link)
				max->link = ft_ullintlen(tab[i]->lstat.st_nlink);
			if ((int)ft_strlen(pwd->pw_name) > max->uid)
				max->uid = ft_strlen(pwd->pw_name);
			if ((int)ft_strlen(grp->gr_name) > max->gp)
				max->gp = ft_strlen(grp->gr_name);
			if (ft_ullintlen(tab[i]->lstat.st_size) > max->size_majmin)
				max->size_majmin = ft_ullintlen(tab[i]->lstat.st_size);
			if (S_ISBLK(tab[i]->lstat.st_mode) || S_ISCHR(tab[i]->lstat.st_mode))
			{
				if (max->size_majmin < 8)
					max->size_majmin = 8;
			}
			i++;
		}
	}
	return (max);
}

char			*ft_malloc_display(t_path *tab, t_max_optl *max)
{
	char	*display;
	int		len;
	char	*buf_link;
	int		i;

	display = NULL;
	len = 31
		+ max->link 
		+ max->uid
		+ max->gp
		+ max->size_majmin
		+ ft_strlen(tab->display);
	if (S_ISLNK(tab->lstat.st_mode))
	{
		if (!(buf_link = ft_get_link(tab->name)))
			return (NULL);
		len = len
			+ 4
			+ ft_strlen(buf_link);
		ft_strdel(&buf_link);
	}
	if (!(display = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		display[i] = ' ';
	return (display);
}

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
	tab->display[1] = ((tab->lstat.st_mode & S_IRUSR) == S_IRUSR) ? 'r': '-';
	tab->display[2] = ((tab->lstat.st_mode & S_IWUSR) == S_IWUSR) ? 'w': '-';
	tab->display[3] = ((tab->lstat.st_mode & S_IXUSR) == S_IXUSR) ? 'x': '-';
	tab->display[4] = ((tab->lstat.st_mode & S_IRGRP) == S_IRGRP) ? 'r': '-';
	tab->display[5] = ((tab->lstat.st_mode & S_IWGRP) == S_IWGRP) ? 'w': '-';
	tab->display[6] = ((tab->lstat.st_mode & S_IXGRP) == S_IXGRP) ? 'x': '-';
	tab->display[7] = ((tab->lstat.st_mode & S_IROTH) == S_IROTH) ? 'r': '-';
	tab->display[8] = ((tab->lstat.st_mode & S_IWOTH) == S_IWOTH) ? 'w': '-';
	tab->display[9] = ((tab->lstat.st_mode & S_IXOTH) == S_IXOTH) ? 'x': '-';
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

void			ft_nlink(t_path *tab, t_max_optl *max)
{
	ft_fill_nbr(tab->display + 11 + max->link, tab->lstat.st_nlink);
}

void			ft_uid(t_path *tab, t_max_optl *max)
{
	int				i;
	int				j;
	struct passwd	*pwd;

	pwd = getpwuid(tab->lstat.st_uid);
	i = 13 + max->link;
	j = 0;
	while (j < (int)ft_strlen(pwd->pw_name))
	{
		tab->display[i] = pwd->pw_name[j];
		i++;
		j++;
	}
}

void			ft_grp(t_path *tab, t_max_optl *max)
{
	int				i;
	int				j;
	struct group	*grp;

	grp = getgrgid(tab->lstat.st_gid);
	i = 15 + max->link + max->uid;
	j = 0;
	while (j < (int)ft_strlen(grp->gr_name))
	{
		tab->display[i] = grp->gr_name[j];
		i++;
		j++;
	}
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

void			ft_name(t_path *tab, t_max_optl *max, char *tmp_display)
{
	int		i;
	int		j;
	char	*buf_link;

	i = 31 + max->link + max->uid + max->gp + max->size_majmin;
	j = 0;
	while (tmp_display[j])
	{
		tab->display[i] = tmp_display[j];
		i++;
		j++;
	}
	if (S_ISLNK(tab->lstat.st_mode))
	{
		tab->display[i + 1] = '-';
		tab->display[i + 2] = '>';
		i = i + 4;
		if (!(buf_link = ft_get_link(tab->name)))
			return ;
		j = 0;
		while (buf_link[j])
		{
			tab->display[i] = buf_link[j];
			i++;
			j++;
		}
		ft_strdel(&buf_link);
	}
}

void			ft_acl_xatt(t_path *tab)
{
	acl_t	acl;

	if (S_ISLNK(tab->lstat.st_mode))
	{
		acl = acl_get_link_np(tab->name, ACL_TYPE_EXTENDED);
		if (acl)
			tab->display[10] = '+';
		if ((int)listxattr(tab->name, NULL, 0, XATTR_NOFOLLOW) > 0)
			tab->display[10] = '@';
		acl_free((void *)acl);
	}
	else
	{
		acl = acl_get_file(tab->name, ACL_TYPE_EXTENDED);
		if (acl)
			tab->display[10] = '+';
		if ((int)listxattr(tab->name, NULL, 0, 0) > 0)
			tab->display[10] = '@';
		acl_free((void *)acl);
	}
}
void			ft_fill_display(t_path *tab, t_max_optl *max, char *tmp_display)
{
	ft_type(tab);
	ft_access(tab);
	ft_acl_xatt(tab);
	ft_nlink(tab, max);
	ft_uid(tab, max);
	ft_grp(tab, max);
	ft_size_majmin(tab, max);
	ft_date(tab, max);
	ft_name(tab, max, tmp_display);
}

void			ft_print_total(t_path **tab)
{
	int		i;
	int		blocks;
	char	*tmp_name;

	if (!tab)
		return ;
	i = 0;
	blocks = 0;
	while (tab[i])
	{
		if (ft_strrchr(tab[i]->name, '/') != NULL)
			tmp_name = ft_strrchr(tab[i]->name, '/') + 1;
		else
			tmp_name = tab[i]->name;
		if (ft_strcmp(tmp_name, ".") != 0 && ft_strcmp(tmp_name, "..") != 0)
			blocks = blocks + tab[i]->lstat.st_blocks;
		i++;
	}
	ft_putstr("total ");
	ft_putnbr_endl(blocks);
}
/*char			*ft_get_total(t_path **tab)
{
	int		i;
	int		blocks;
	char	*tmp_name;
	char	*total;

	i = 0;
	blocks = 0;
	while (tab[i])
	{
		if (ft_strrchr(tab[i]->name, '/') != NULL)
			tmp_name = ft_strrchr(tab[i]->name, '/') + 1;
		else
			tmp_name = tab[i]->name;
		if (ft_strcmp(tmp_name, ".") != 0 && ft_strcmp(tmp_name, "..") != 0)
			blocks = blocks + tab[i]->lstat.st_blocks;
		i++;
	}
	total = ft_strnew(6 + ft_ullintlen(blocks));
	total = ft_strcpy(total, "total ");
	ft_fill_nbr(total + ft_strlen(total) + ft_ullintlen(blocks) - 1, blocks);
	return (total);
}*/
	char			*tmp_display;

void			ft_opt_l(t_path **tab, char *opt)
{
	t_max_optl		*max;
	int				i;
	char			*tmp_display;

	if (opt['l'] == 0)
		return ;
	if ((max = ft_get_max(tab)) == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		if (!(tab[i]->display))
			i++;
		else
		{
			tmp_display = tab[i]->display;
			if (!(tab[i]->display = ft_malloc_display(tab[i], max)))
				return ;
			ft_fill_display(tab[i], max, tmp_display);
			i++;
		}
	}
	free(max);
}
