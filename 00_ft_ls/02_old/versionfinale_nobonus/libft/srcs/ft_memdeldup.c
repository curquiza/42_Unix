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

int		ft_memdeldup(void **dst, void *src, size_t size)
{
	if (!dst || !src)
		return (-1);
	ft_memdel(dst);
	if (!(*dst = ft_memalloc(size)))
		return (-1);
	ft_memcpy(*dst, src, size);
	return (0);
}
