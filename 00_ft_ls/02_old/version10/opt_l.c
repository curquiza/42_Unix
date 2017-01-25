/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:24:53 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/20 17:48:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_check_max et ft_get_max :
** Remplissent la structure de type t_max_optl nécessaire au padding pour
** l'affichage du long format
*/

void			ft_check_max(t_path *tab, t_max_optl *max)
{
	struct group	*grp;
	struct passwd	*pwd;

	pwd = getpwuid(tab->lstat.st_uid);
	grp = getgrgid(tab->lstat.st_gid);
	if (ft_ullintlen(tab->lstat.st_nlink) > max->link)
		max->link = ft_ullintlen(tab->lstat.st_nlink);
	if ((int)ft_strlen(pwd->pw_name) > max->uid)
		max->uid = ft_strlen(pwd->pw_name);
	if ((int)ft_strlen(grp->gr_name) > max->gp)
		max->gp = ft_strlen(grp->gr_name);
	if (ft_ullintlen(tab->lstat.st_size) > max->size_majmin)
		max->size_majmin = ft_ullintlen(tab->lstat.st_size);
	if (S_ISBLK(tab->lstat.st_mode) || S_ISCHR(tab->lstat.st_mode))
	{
		if (max->size_majmin < 8)
			max->size_majmin = 8;
	}
}

t_max_optl		*ft_get_max(t_path **tab)
{
	t_max_optl		*max;
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
		if (tab[i]->display != NULL)
			ft_check_max(tab[i], max);
		i++;
	}
	return (max);
}

/*
** ft_malloc_display :
** malloc le champs display de la taille nécessaire
*/

char			*ft_malloc_display(t_path *tab, t_max_optl *max)
{
	char	*display;
	int		len;
	char	*buf_link;
	int		i;

	display = NULL;
	len = 31 + max->link + max->uid + max->gp + max->size_majmin
		+ ft_strlen(tab->display);
	if (S_ISLNK(tab->lstat.st_mode))
	{
		if (!(buf_link = ft_get_link(tab->name)))
			return (NULL);
		len = len + 4 + ft_strlen(buf_link);
		ft_strdel(&buf_link);
	}
	if (!(display = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		display[i] = ' ';
	return (display);
}

/*
** ft_fill_display :
** Remplit le champs display avec les informations du file
*/

void			ft_fill_display(t_path *tab, t_max_optl *max, char *tmp_display)
{
	ft_type(tab);
	ft_access(tab);
	ft_acl_xatt(tab);
	ft_fill_nbr(tab->display + 11 + max->link, tab->lstat.st_nlink);
	ft_uid_grp(tab, max);
	ft_size_majmin(tab, max);
	ft_date(tab, max);
	ft_name(tab, max, tmp_display);
}

/*
** ft_opt_l :
** Activation de l'option l
*/

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
		if (tab[i]->display)
		{
			tmp_display = tab[i]->display;
			if (!(tab[i]->display = ft_malloc_display(tab[i], max)))
				return ;
			ft_fill_display(tab[i], max, tmp_display);
		}
		i++;
	}
	free(max);
}
