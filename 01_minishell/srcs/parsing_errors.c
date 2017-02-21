/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 11:36:56 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/09 18:02:33 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** ft_check_quote :
** Returns -1 if problem with quotes (' and ") in the command = btw two ';'
** Otherwise, returns 0.
*/

int		ft_check_quote(char *line)
{
	while (*line)
	{
		if (*line == 39 || *line == '"')
		{
			if (*(line + 1) == '\0' || ft_strchr(line + 1, *line) == NULL)
			{
				ft_putendl_fd("minishell: quote error", 2);
				return (-1);
			}
			line = ft_strchr(line + 1, *line) + 1;
		}
		else
			line++;
	}
	return (0);
}

/*
** ft_check_line :
** Returns -1 if two ';' or if only blanks and ';' in the complete command line
** Otherwise, returns 0.
*/

int		ft_check_line(char *line)
{
	int		i;
	int		blank;

	if (!line || !line[0])
		return (-1);
	blank = 0;
	if (line[0] == ' ' || line[0] == '\t' || line[0] == ';')
		blank++;
	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == ';' && line[i + 1] == ';')
		{
			ft_putendl_fd("minishell: parse error near ';;'", 2);
			return (-1);
		}
		if (line[i + 1] == ' ' || line[i + 1] == '\t' || line[i + 1] == ';')
			blank++;
		i++;
	}
	if (blank == i + 1)
		return (-1);
	return (0);
}
