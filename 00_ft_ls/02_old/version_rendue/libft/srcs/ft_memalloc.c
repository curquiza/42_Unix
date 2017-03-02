/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:57:33 by curquiza          #+#    #+#             */
/*   Updated: 2016/11/20 14:52:57 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*mem;

	if (!(mem = (char *)malloc(sizeof(*mem) * size)))
		return (NULL);
	while (size--)
		mem[size] = 0;
	return ((void *)mem);
}
