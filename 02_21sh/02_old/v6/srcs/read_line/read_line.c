/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 17:03:09 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/29 17:15:39 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_termput(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_interpreter(char *buff, t_tc *tool)
{
	if (buff[0] == '\n')
	{
		if (tool->ctrl_r == 0)
		{
			ft_add_histo_line(tool, &g_shell->histo_ctrl->start, g_shell->histo_ctrl);
			ft_insert_eol(tool);
		}
		else
			ft_put_ctrl_r_rslt(tool, g_shell->histo_ctrl);
	}
	if (ft_isprint(buff[0]) == 1)
		ft_insert(buff, tool);
	if (buff[0] == 127)
		ft_delete_back(tool);
	if (buff[0] == 27 && buff[2] == 51 && buff[3] == 126)
		ft_delete_front(tool);
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		ft_move_left(tool);
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		ft_move_right(tool);
	if ((buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 65)
		|| (buff[0] == 27 && buff[1] == 91 && buff[2] == 53 && buff[3] == 126))
		ft_move_up(tool);
	if ((buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 66)
		|| (buff[0] == 27 && buff[1] == 91 && buff[2] == 54 && buff[3] == 126))
		ft_move_down(tool);
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 72) || buff[0] == 1)
		ft_move_start(tool);
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 70) || buff[0] == 5)
		ft_move_end(tool);
	if (buff[0] == 2)
		ft_move_word_left(tool);
	if (buff[0] == 6)
		ft_move_word_right(tool);
	if (buff[0] == 11)
		ft_copy(tool);
	if (buff[0] == 24)
		ft_cut(tool);
	if (buff[0] == 22)
		ft_insert(tool->tmp, tool);
	if (buff[0] == 4)
		ft_ctrl_d(tool);
	if (buff[0] == 18 && tool->ctrl_r == 0)
		ft_ctrl_r(tool);

	if (tool->ctrl_r == 0)
	{
		if (buff[0] == 9)
			ft_completion(tool, g_shell->comp_ctrl);
		ft_reset_compl(g_shell->comp_ctrl);
	}

	if (tool->ctrl_r == 0)
	{
		if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65)
			ft_histo_up(tool, g_shell->histo_ctrl);
		else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66)
			ft_histo_down(tool, g_shell->histo_ctrl);
		else
			g_shell->histo_ctrl->pos = 0;
	}
}

void		ft_read_line(char **line, int prompt_len)
{
	//t_tc	tool;
	char	little_buff[5];

	ft_strdel(line);
	ft_init_tc();
	ft_init_struct_tc(g_shell->tc_tool, prompt_len);
	while (g_shell->tc_tool->stop == 0)
	{
		ft_bzero(little_buff, 5);
		read(0, little_buff, 4);
	//	ft_putnbr2("buff[0] = ", little_buff[0]);
	//	ft_putnbr2("buff[1] = ", little_buff[1]);
	//	ft_putnbr2("buff[2] = ", little_buff[2]);
	//	ft_putnbr2("buff[3] = ", little_buff[3]);
	//	ft_putnbr2("buff[4] = ", little_buff[4]);
		ft_interpreter(little_buff, g_shell->tc_tool);
	}
	//ft_putendl2_fd("g_shell->tc_tool->buff = ", g_shell->tc_tool->buff, 1);
	//ft_putnbr2("x_max = ", g_shell->tc_tool->x_max);
	//ft_putnbr2("curs_x = ", g_shell->tc_tool->curs_x);
	//ft_putnbr2("curs_y = ", g_shell->tc_tool->curs_y);
	//ft_putnbr2("nbr_char = ", g_shell->tc_tool->nbr_char);
	//ft_putendl("");
	ft_putendl("");
	*line = ft_strdup(g_shell->tc_tool->buff);
	ft_reset_tc(g_shell->tc_tool);
}
