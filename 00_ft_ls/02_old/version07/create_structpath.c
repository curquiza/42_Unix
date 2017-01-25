/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:54:08 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/14 12:16:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** ft_get_lst_in :
** Renvoie une liste chainée de type t_list.
** Cette liste contient les noms des files dans le dossier filename.
** Si l'acces au fichier est refusé, permerror est mis à 1.
*/

t_list		*ft_get_lst_in(char *filename, char *opt)
{
	DIR				*dirp;
	struct dirent	*ret_read;
	t_list			*lst_in;

	if (!(dirp = opendir(filename)))
		return (NULL);
	lst_in = NULL;
	while ((ret_read = readdir(dirp)))
	{
		if (ret_read->d_name[0] == '.' && opt['a'] == 0)
			continue ;
		ft_lstadd_back(&lst_in, ft_lstnew(ret_read->d_name,
					ft_strlen(ret_read->d_name) + 1));
	}
	if (dirp)
		closedir(dirp);
	return (lst_in);
}

/*
** ft_new_structpath :
** Renvoie l'adresse d'une struct s_path mallocée.
** Si le filename est un fichier existant, remplit les champs display et lst_in
** Le path (le chemin complet) va dans name, et le nom du file dans display
*/

t_path		*ft_new_structpath(char *filename, char *path, char *opt)
{
	t_path		*new;
	int			ret;

	if (!(new = (t_path *)malloc(sizeof(*new))))
		return (NULL);
	errno = 0;
	if (ft_strcmp(path, "/") == 0 || ft_strcmp(path, "") == 0)
		new->name = ft_strjoin(path, filename);
	else
		new->name = ft_strjoin3(path, "/", filename);
	new->display = NULL;
	new->lst_in = NULL;
	new->inside = NULL;
	if ((ret = lstat(new->name, &(new->lstat))) >= 0)
	{
		new->display = filename;
		new->lst_in = ft_get_lst_in(new->name, opt);
	}
	new->error = errno;
	if (S_ISLNK(new->lstat.st_mode))
		stat(new->name, &new->stat);
	return (new);
}

/*
** ft_init_insidetab :
** Sous fonction de ft_new_inside pour palier à la norme.
** Alloue la mémoire suffisante pour le tab inside, et remplit cpt.
*/

t_path		**ft_init_insidetab(int *cpt, t_list *lst_in)
{
	t_path	**inside;

	*cpt = ft_lstlen(lst_in);
	if (*cpt == 0)
		return (NULL);
	if (!(inside = (t_path **)malloc(sizeof(*inside) * (*cpt + 1))))
		return (NULL);
	inside[*cpt] = NULL;
	return (inside);
}

/*
** ft_new_pathtab :
** Renvoie l'adresse d'un tab de type t_path (mallocé) se terninant par un
** pointeur NULL, à partir de l'adresse d'une struct s_path passée en paramètre.
*/

t_path		**ft_new_inside(t_path *path, char *opt)
{
	int			cpt;
	int			i;
	t_list		*current;
	t_path		**inside;

	if ((inside = ft_init_insidetab(&cpt, path->lst_in)) == NULL)
		return (NULL);
	i = 0;
	current = path->lst_in;
	while (i < cpt)
	{
		inside[i] = ft_new_structpath(current->content, path->name, opt);
		i++;
		current = current->next;
	}
	ft_sortascii_pathtab(inside);
	return (inside);
}
