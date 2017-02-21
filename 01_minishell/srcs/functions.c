/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:02:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/07 10:58:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		ft_isblank(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			return (0);
		s++;
	}
	return (1);
}

int		ft_strisalnum(char *s)
{
	while (*s)
	{
		if (ft_isalnum(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}

void	ft_comdel(t_command ***com)
{
	int		i;

	if (!com || !(*com))
		return ;
	i = 0;
	while ((*com)[i])
	{
		ft_strdel(&(*com)[i]->bin);
		ft_tabdel(&(*com)[i]->arg);
		free((*com)[i]);
		(*com)[i] = NULL;
		i++;
	}
	free(*com);
	*com = NULL;
}
