/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:54:08 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/02 12:21:30 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

/*
** Version de sauvegarde pour avoir les * et les parenthèses qui semblent 
** inutiles lors de la manip des tableaux de structures dabs la structure
*/

t_list		*ft_get_lst_in(char *path)
{
	DIR				*dirp;
	struct dirent	*ret_read;
	t_list			*lst_in;

	if (!(dirp = opendir(path)))
		return (NULL);
	lst_in = NULL;
	while ((ret_read = readdir(dirp)))
	{
		ft_lstadd_back(&lst_in, ft_lstnew(ret_read->d_name,
					ft_strlen(ret_read->d_name) + 1));
	}
	return (lst_in);
}

void		ft_init_structpath(char *path, t_path *new)
{
	new->name = ft_strdup(path);
	if (lstat(path, &(new->stat)) >= 0)
	{
		new->display = ft_strdup(path);
		if (S_ISDIR(new->stat.st_mode) && ft_strcmp(new->name, ".") != 0
				&& ft_strcmp(new->name, "..") != 0)
			new->used_optR = 1;
		new->lst_in = ft_get_lst_in(path);
	}
	new->inside = NULL;
}

t_path		*ft_new_structpath(char *path)
{
	t_path		*new;
	char		*tmppath;
	int			cpt;
	int			i;
	t_list		*current;

	if (!(new = (t_path *)malloc(sizeof(*new))))
		return (NULL);
	ft_init_structpath(path, new);
	cpt = ft_lstlen(new->lst_in);
	//if (!(new->inside = (t_path **)malloc(sizeof(*(new->inside)) * (cpt + 1))))
	if (!(new->inside = (t_path **)malloc(sizeof(*new->inside) * (cpt + 1))))
		return (NULL);
	(new->inside)[cpt] = NULL;
	i = -1;
	current = new->lst_in;
	while (++i < cpt)
	{
		//if (!((new->inside)[i] = (t_path *)malloc(sizeof(*((new->inside)[i])))))
		if (!(new->inside[i] = (t_path *)malloc(sizeof(*new->inside[i]))))
			return (NULL);
		tmppath = ft_strjoin3(path, "/", current->content);
		//ft_init_structpath(tmppath, (new->inside)[i]);
		ft_init_structpath(tmppath, new->inside[i]);
		ft_strdel(&tmppath);
		current = current->next;
	}
	return (new);
}
