/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 17:50:35 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/18 17:30:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*void	ft_add_char(t_tc *tool, char c)
{
	int		pos;
	char	*tmp;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	tmp = ft_strdup(tool->buff);
	ft_bzero(tool->buff, TC_SIZE);
	ft_strncpy(tool->buff, tmp, pos);
	tool->buff[pos] = c;
	ft_strcpy(tool->buff + pos + 1, tmp + pos);
	tool->nbr_char++;
	ft_strdel(&tmp);
}*/

/*static void		ft_adjust_cursor(t_tc *tool)
{
	tool->curs_x++;
	if (tool->curs_x > tool->x_max)
	{
		tool->curs_x = 0;
		tool->curs_y++;
		tputs(tool->down, 1, ft_termput);
		tputs(tgetstr("cr", NULL), 1, ft_termput);
//		if (tool->curs_y > tool->y_max)
//			tool->y_max++;
	}
	else
		tputs(tool->right, 1, ft_termput);
}*/

/*void	ft_insert_char(char *buff, t_tc *tool)
{
//	int		nbr_line;

	if (tool->nbr_char >= TC_SIZE - 2)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else
	{
		ft_clear_all_lines(tool);
		ft_add_char(tool, buff[0]);
//		tputs(tgetstr("im", NULL), 1, ft_termput); // ?
		write(1, tool->buff, ft_strlen(tool->buff));
//		tputs(tgetstr("ei", NULL), 1, ft_termput); //?
		ft_replace_cursor(tool);
		//ft_adjust_cursor(tool);
		ft_move_right(tool);
//		nbr_line = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
//		if (nbr_line > tool->y_max + 1)
//			tool->y_max = nbr_line - 1;
	}
}*/

void	ft_add_n_char(t_tc *tool, char *buff, int pos, int len)
{
	char	*tmp;

	if (len > (int)ft_strlen(buff))
		len = ft_strlen(buff);
	tmp = ft_strdup(tool->buff);
	ft_bzero(tool->buff, TC_SIZE);
	ft_strncpy(tool->buff, tmp, pos);
	ft_strncpy(tool->buff + pos, buff, len);
	ft_strcpy(tool->buff + pos + len, tmp + pos);
	tool->nbr_char = tool->nbr_char + len;
	ft_strdel(&tmp);
}

/*void	ft_insert_char(char *buff, t_tc *tool)
{
	int 	pos;

	if (tool->nbr_char >= TC_SIZE - 2)
	{
		tputs(tgetstr("bl", NULL), 1, ft_termput);
		return ;
	}
	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	ft_clear_all_lines(tool);
	ft_add_n_char(tool, buff, pos, 1);
	write(1, tool->buff, ft_strlen(tool->buff));
	ft_replace_cursor(tool);
	ft_move_right(tool);
}*/

void	ft_insert(char *buff, t_tc *tool)
{
	int 	pos;
	int		i;
	int		len;

	if (tool->nbr_char + ft_strlen(buff) >= TC_SIZE - 2)
	{
		tputs(tgetstr("bl", NULL), 1, ft_termput);
		return ;
	}
	len = ft_strlen(buff);
	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	ft_clear_all_lines(tool);
	ft_add_n_char(tool, buff, pos, len);
	ft_clean_buff(tool);
	write(1, tool->buff, ft_strlen(tool->buff));
	ft_replace_cursor(tool);
	i = -1;
	while (++i < len)
		ft_move_right(tool);
}

void	ft_insert_eol(t_tc *tool)
{
	if (tool->nbr_char >= TC_SIZE - 1)
	{
		tool->buff[TC_SIZE - 2] = '\n';
		tool->buff[TC_SIZE - 1] = '\0';
	}
	else
		tool->buff[tool->nbr_char] = '\n';
	tool->stop = 1;
}
