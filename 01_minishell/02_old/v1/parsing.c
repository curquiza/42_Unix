/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:45:51 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/03 16:06:36 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_command	**ft_create_comtab(char **split, int size)
{
	int			i;
	int			j;
	t_command	**com;

	if (!(com = (t_command **)malloc(sizeof(*com) * (size + 1))))
		return (NULL);
	com[size] = NULL;
	i = 0;
	j = 0;
	while (split[i])
	{
		if (ft_isblank(split[i]) == 0)
		{
			if (!(com[j] = (t_command *)malloc(sizeof(**com))))
				return (NULL);
			com[j]->bin = ft_get_onearg(split[i]);
			com[j]->arg = ft_add_arg(split[i], com[j]->bin);
			j++;
		}
		i++;
	}
	return (com);
}

t_command	**ft_get_commands(char *line)
{
	t_command	**comtab;
	char		**split;
	int			size;
	int			i;

	if (ft_check_line(line) == -1)
		return (NULL);
	split = ft_comsplit(line);
	size = 0;
	i = 0;
	while (split[i])
	{
		if (ft_check_quote(split[i]) == -1)
		{
			ft_tabdel(&split);
			return (NULL);
		}
		if (ft_isblank(split[i]) == 0)
			size++;
		i++;
	}
	comtab = ft_create_comtab(split, size);
	//ft_putendl("les arg :");
	//ft_puttab(comtab[0]->arg);
	ft_tabdel(&split);
	return (comtab);
}
