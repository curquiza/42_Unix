/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:59:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 16:08:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_strjoin3 :
** Comme strjoin mais pour 3 chaines de caractères.
*/

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;

	if (!s1 || !s2 || !s3)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(*tmp) * (ft_strlen(s1) + ft_strlen(s2)
													+ ft_strlen(s3) + 1))))
		return (NULL);
	ft_strcpy(tmp, s1);
	tmp = tmp + ft_strlen(s1);
	ft_strcpy(tmp, s2);
	tmp = tmp + ft_strlen(s2);
	ft_strcpy(tmp, s3);
	tmp = tmp - ft_strlen(s1) - ft_strlen(s2);
	return (tmp);
}

/*
** ft_pathtablen :
** Calcule la taille d'un tableau de type t_path. Le dernier élément est NULL.
*/

int		ft_pathtablen(t_path **tab)
{
	int		cpt;

	cpt = 0;
	if (!tab)
		return (0);
	while (tab[cpt])
		cpt++;
	return (cpt);
}

/*
** ft_toopen :
** Ckeck si un file doit être ouvert (1) ou non (0)
*/

int		ft_toopen(t_path *path, char *opt, int is_start)
{
	if (path->display == NULL)
		return (0);
	if (opt['d'] == 1)
		return (0);
	if (S_ISDIR(path->lstat.st_mode))
		return (1);
	if (S_ISLNK(path->lstat.st_mode))
	{
		if (opt['l'] == 1)
			return (0);
		if (S_ISDIR(path->stat.st_mode) && is_start == 0)
			return (0);
		if (S_ISDIR(path->stat.st_mode) && is_start == 1)
			return (1);
	}
	return (0);
}

/*
** ft_fll_nbr :
** Remplit str avec le nombre value.
** /!\ Remplit par la fin, donc str doit être adaptée.
*/

void	ft_fill_nbr(char *str, unsigned long long int value)
{
	int		i;

	if (value == 0)
		*str = '0';
	i = 0;
	while (value != 0)
	{
		str[i] = '0' + value % 10;
		value = value / 10;
		i--;
	}
}

/*
** ft_name_in_path :
** Retourne le nom du file en se basant sur son chemin.
*/

char	*ft_name_in_path(char *path)
{
	char	*name;

	if (ft_strrchr(path, '/') != NULL)
		name = ft_strrchr(path, '/') + 1;
	else
		name = path;
	return (name);
}
