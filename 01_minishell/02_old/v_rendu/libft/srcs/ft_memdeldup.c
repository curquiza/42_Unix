/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdeldup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 18:04:41 by curquiza          #+#    #+#             */
/*   Updated: 2016/12/28 18:04:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Supprime et free dst, puis malloc dst et copie src dans dst
** Retourne -1 en cas d'erreur, 0 sinon.
*/

void	*ft_memdeldup(void **src, size_t size)
{
	void	*tmp;

	if (!src)
		return (NULL);
	tmp = ft_memalloc(size);
	ft_memcpy(tmp, *src, size);
	ft_memdel(src);
	return (tmp);
}
