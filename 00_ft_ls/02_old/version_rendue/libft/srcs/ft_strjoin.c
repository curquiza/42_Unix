/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:16:01 by curquiza          #+#    #+#             */
/*   Updated: 2016/12/09 16:41:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Si l'un des deux est NULL je renvoie le strdup de l'autre
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(tmp, s1);
	tmp = tmp + ft_strlen(s1);
	ft_strcpy(tmp, s2);
	tmp = tmp - (ft_strlen(s1));
	return (tmp);
}
