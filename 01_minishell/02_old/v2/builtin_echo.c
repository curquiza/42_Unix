/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:18:47 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/04 17:21:04 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** ft_echo_flagn :
** Returns 0 if a new line at the end of the line is needed (default flag).
** Returns 1 if the flag -n is activated, then no new line needed.
*/

int		ft_echo_flagn(char **arg)
{
	int		j;

	if (arg[1])
	{
		if (ft_strncmp(arg[1], "-n", 2) == 0)
		{
			j = 1;
			while (arg[1][j] == 'n')
				j++;
			if (j != (int)ft_strlen(arg[1]))
				return (0);
			else
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

/*
** ft_echo_argindex :
** Returns the index of the first argument (not flag) of echo.
*/

int		ft_echo_argindex(char **arg)
{
	int		i;
	int		j;

	i = 1;
	while (arg[i])
	{
		if (ft_strncmp(arg[i], "-n", 2) == 0)
		{
			j = 1;
			while (arg[i][j] == 'n')
				j++;
			if (j != (int)ft_strlen(arg[i]))
				return (i);
		}
		else if (ft_strcmp(arg[i], "-") == 0)
			return (i + 1);
		else
			return (i);
		i++;
	}
	return (i);
}

/*
** ft_echo & ft_echo_printarg :
** Same bhvr than the builtin "echo" from the shell
*/

void	ft_echo_printarg(char *arg)
{
	int		j;

	if (!ft_strstr(arg, "\n"))
	{
		j = 0;
		while (arg[j])
		{
			if (ft_strncmp(arg + j, "\\n", 2) == 0)
			{
				ft_putchar('\n');
				j++;
			}
			else
				ft_putchar(arg[j]);
			j++;
		}
	}
	else
		ft_putstr(arg);
}

void	ft_echo(char **arg)
{
	int		index;
	int		last;

	last = ft_tablen(arg) - 1;
	index = ft_echo_argindex(arg);
	while (arg[index])
	{
		ft_echo_printarg(arg[index]);
		if (index != last)
			ft_putchar(' ');
		index++;
	}
	if (ft_echo_flagn(arg) == 0)
		ft_putchar('\n');
	exit(0);
}
