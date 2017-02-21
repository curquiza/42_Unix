/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:07:30 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/03 12:20:58 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** In this file :
** Splits the command line in different commands in case of multi commands with
** the separator ';' (minishell's bonus)
*/

int		ft_countcom(char *s)
{
	int		cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != ';')
		{
			cnt++;
			while (*s && *s != ';')
			{
				if (*s == 39 || *s == '"')
				{
					if (ft_strchr(s + 1, *s))
						s = ft_strchr(s + 1, *s);
				}
				s++;
			}
		}
		else
			s++;
	}
	return (cnt);
}

int		ft_comlen(char *s)
{
	int		len;
	char	quote;

	len = 0;
	while (*s && *s != ';')
	{
		len++;
		if (*s == 39 || *s == '"')
		{
			quote = *s;
			s++;
			if (ft_strchr(s + 1, quote))
			{
				while (*s != quote)
				{
					len++;
					s++;
				}
			}
			len++;
		}
		s++;
	}
	return (len);
}

char	**ft_comsplit(char *s)
{
	char	**tmp;
	int		i;
	int		j;
	int		nb_com;

	i = 0;
	if (!s)
		return (NULL);
	nb_com = ft_countcom(s);
	//ft_putstr("nb commandes = ");
	//ft_putnbr_endl(nb_com);
	if (!(tmp = (char **)malloc(sizeof(*tmp) * (nb_com + 1))))
		return (NULL);
	tmp[nb_com] = NULL;
	while (i < nb_com)
	{
		while (*s && *s == ';')
			s++;
		j = ft_comlen(s);
		tmp[i] = ft_strsub(s, 0, j);
		while (j--)
			s++;
		i++;
	}
	//ft_putendl("-------");
	return (tmp);
}
