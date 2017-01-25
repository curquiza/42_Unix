/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_xattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 10:58:11 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/23 11:12:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void			ft_acl_xatt(t_path *tab, char *opt)
{
	acl_t		acl;
	struct stat	tmp;

	if (opt['L'] == 1)
		lstat(tab->name, &tmp);
	else
		tmp = tab->lstat;
	if (S_ISLNK(tmp.st_mode))
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
