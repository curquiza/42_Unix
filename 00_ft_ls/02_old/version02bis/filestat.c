/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filestat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 15:35:04 by curquiza          #+#    #+#             */
/*   Updated: 2016/12/31 17:25:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** Créée la structure filestat qui contient elle même une structure stat
** et divers variables dont le nom du file (qui n'est pas dans la struc stat)
** Retourne l'adresse d'une struct filestat si ok, sinon, retourne NULL.
*/


t_filestat	*ft_new_filestat(char *filename)
{
	struct stat		tmp;
	t_filestat		*rslt;

	if (lstat(filename, &tmp) < 0)
		return (NULL);
	if (!(rslt = (t_filestat *) malloc(sizeof(t_filestat))))
		return (NULL);
	rslt->name = ft_strdup(filename);
	rslt->structstat = tmp;
	return (rslt);
}
