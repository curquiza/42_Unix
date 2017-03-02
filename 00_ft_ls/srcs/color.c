/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 19:53:08 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/25 19:23:00 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_print_color :
** Imprime le nom en couleur en fonction du type de file
*/

void	ft_print_color(char *str, t_path *tab)
{
	S_ISDIR(tab->lstat.st_mode) ? ft_putstr_col(str, DIR_COL, DEF) : 0;
	S_ISLNK(tab->lstat.st_mode) ? ft_putstr_col(str, LNK_COL, DEF) : 0;
	S_ISBLK(tab->lstat.st_mode) ? ft_putstr_col(str, BLK_COL, DEF) : 0;
	S_ISCHR(tab->lstat.st_mode) ? ft_putstr_col(str, CHR_COL, DEF) : 0;
	S_ISSOCK(tab->lstat.st_mode) ? ft_putstr_col(str, SOCK_COL, DEF) : 0;
	S_ISFIFO(tab->lstat.st_mode) ? ft_putstr_col(str, FIFO_COL, DEF) : 0;
	if (S_ISREG(tab->lstat.st_mode))
	{
		if ((tab->lstat.st_mode & S_IXUSR) == S_IXUSR
			|| (tab->lstat.st_mode & S_IXGRP) == S_IXGRP
			|| (tab->lstat.st_mode & S_IXOTH) == S_IXOTH)
			ft_putstr_col(str, EXEC_COL, DEF);
		else
			ft_putstr(str);
	}
}

/*
** ft_find_position :
** Trouve la position du nom à mettre en couleur
*/

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
