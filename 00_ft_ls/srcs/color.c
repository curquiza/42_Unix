/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 19:53:08 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/24 12:43:40 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_putstr_color(char *display, char *color)
{
	ft_putstr(color);
	ft_putstr(display);
	ft_putstr(DEF);
}

void	ft_putendl_color(char *display, char *color)
{
	ft_putstr(color);
	ft_putstr(display);
	ft_putendl(DEF);
}

void	ft_print_color(char *str, t_path *tab)
{
	S_ISREG(tab->lstat.st_mode) ? ft_putstr_color(str, DEF) : 0;
	S_ISDIR(tab->lstat.st_mode) ? ft_putstr_color(str, BLUE_BOLD) : 0;
	S_ISLNK(tab->lstat.st_mode) ? ft_putstr_color(str, GREEN_BOLD) : 0;
	S_ISBLK(tab->lstat.st_mode) ? ft_putstr_color(str, CYAN) : 0;
	S_ISCHR(tab->lstat.st_mode) ? ft_putstr_color(str, PINK) : 0;
	S_ISSOCK(tab->lstat.st_mode) ? ft_putstr_color(str, RED_BOLD) : 0;
	S_ISFIFO(tab->lstat.st_mode) ? ft_putstr_color(str, RED) : 0;
}

int		ft_find_position(t_path *tab, char *name, int len)
{
	int		i;

	i = 0;
	if (S_ISLNK(tab->lstat.st_mode))
	{
		i = 0;
		while (tab->display[i] && ft_strncmp(tab->display + i, "->", 2) != 0)
			i++;
		while (tab->display[i])
		{
			if (ft_strncmp(tab->display + i, name, len) == 0)
				return (i);
			i--;
		}
	}
	else
	{
		i = ft_strlen(tab->display);
		while (tab->display[--i])
		{
			if (ft_strncmp(tab->display + i, name, len) == 0)
				return (i);
		}
	}
	return (i);
}
