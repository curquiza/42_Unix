/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infodir_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:17:52 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 20:49:48 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** Les fonctions de ce fichier remplissent le champs display avec les
** informations récupérées sur le file
*/

char			*ft_get_link(char *name)
{
	char	*buf_link;

	if (!(buf_link = ft_strnew(4096)))
		return (NULL);
	readlink(name, buf_link, 4096);
	return (buf_link);
}

void			ft_name(t_path *tab, t_max_optl *max, char *tmp_display,
						int len_min)
{
	int		i;
	int		j;
	char	*buf_link;

	i = len_min + max->link + max->uid + max->gp + max->size_majmin;
	j = 0;
	while (tmp_display[j])
		tab->display[i++] = tmp_display[j++];
	if (S_ISLNK(tab->lstat.st_mode))
	{
		tab->display[i + 1] = '-';
		tab->display[i + 2] = '>';
		i = i + 4;
		if (!(buf_link = ft_get_link(tab->name)))
			return ;
		j = 0;
		while (buf_link[j])
			tab->display[i++] = buf_link[j++];
		ft_strdel(&buf_link);
	}
}
