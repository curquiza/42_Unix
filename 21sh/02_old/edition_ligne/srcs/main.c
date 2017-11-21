/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 19:26:24 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/10 15:43:56 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tc.h"

int		ft_termput(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_init_tc(void)
{
	char			*name_term;
	struct termios	term;

	name_term = ft_strdup("xterm-256color");
	if (tgetent(NULL, name_term) == 0)
		ft_exit("tgetent error", 1);
	if (tcgetattr(0, &term) == -1)
		ft_exit("tcgetattr error", 1);
	term.c_lflag &= ~ (ICANON);
	term.c_lflag &= ~ (ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit("tcsetattr error", 1);
	ft_strdel(&name_term);
}

void	ft_reset_tc()
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		ft_exit("tcsetattr error", 1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		ft_exit("tcsetattr error", 1);
}

void	ft_init_struct_tc(t_tc *tool, int prompt_len)
{
	struct winsize	*w;
	
	if (!(w = (struct winsize *)malloc(sizeof(*w))))
		return ;
	if (ioctl(1, TIOCGWINSZ, w) != 0)
		ft_exit("ioctl error", 1);
	tool->x_max = w->ws_col - 1;
	free(w);
	tool->y_max = 0;
	ft_bzero(tool->buff, TC_SIZE);
	tool->nbr_char = 0;
	tool->prompt_len = prompt_len;
	tool->curs_x = prompt_len;
	tool->curs_y = 0;
}

void	ft_increase_pos_cursor(t_tc *tool)
{
	if (tool->curs_x == tool->x_max)
	{
		tool->curs_x = 0;
		tool->curs_y++;
		if (tool->curs_y > tool->y_max)
			tool->y_max++;
	}
	else
		tool->curs_x++;
}

void	ft_decrease_pos_cursor(t_tc *tool)
{
	if (tool->curs_x == 0 && tool->curs_y != 0)
	{
		tool->curs_x = tool->x_max;
		tool->curs_y -= 1;
		if (tool->curs_y > tool->y_max)
			tool->y_max += 1;
	}
	else
		tool->curs_x--;
}

void	ft_replace_cursor(t_tc *tool)
{
	int		i;
	
	i = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
	while (i > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_termput);
		i--;
	}
	i = 0;
	while (i < tool->curs_y)
	{
		tputs(tgetstr("do", NULL), 1, ft_termput);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, ft_termput);
	i = 0;
	while (i < tool->curs_x)
	{
		tputs(tgetstr("nd", NULL), 1, ft_termput);
		i++;
	}
}

void	ft_clear_all_lines(t_tc *tool)
{
	int		i;

	i = tool->curs_y + 1;
	while (--i > 0)
		tputs(tgetstr("up", NULL), 1, ft_termput);
	tputs(tgetstr("cr", NULL), 1, ft_termput);
	i = -1;
	while (++i < tool->prompt_len)
		tputs(tgetstr("nd", NULL), 1, ft_termput);
	tputs(tgetstr("ce", NULL), 1, ft_termput);
	if (tool->nbr_char + tool->prompt_len > tool->x_max + 1)
	{
		tputs(tgetstr("do", NULL), 1, ft_termput);
		tputs(tgetstr("cr", NULL), 1, ft_termput);
		tputs(tgetstr("cd", NULL), 1, ft_termput);
		tputs(tgetstr("up", NULL), 1, ft_termput);
		i = -1;
		while (++i < tool->prompt_len)
			tputs(tgetstr("nd", NULL), 1, ft_termput);
	}
}

void	ft_add_char(t_tc *tool, char c)
{
	int		pos;
	char	*tmp;

	pos = tool->curs_y * (tool->x_max + 1) + tool->curs_x - tool->prompt_len;
	tmp = ft_strdup(tool->buff);
	ft_bzero(tool->buff, TC_SIZE);
	ft_strncpy(tool->buff, tmp, pos);
	tool->buff[pos] = c;
	ft_strcpy(tool->buff + pos + 1, tmp + pos);
	ft_strdel(&tmp);
}

void	ft_adjust_cursor(t_tc *tool)
{
	tool->curs_x++;
	if (tool->curs_x > tool->x_max)
	{
		tool->curs_x = 0;
		tool->curs_y++;
		tputs(tgetstr("do", NULL), 1, ft_termput);
		tputs(tgetstr("cr", NULL), 1, ft_termput);
		if (tool->curs_y > tool->y_max)
			tool->y_max++;
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_termput);
}

void	ft_insert_char(char *buff, t_tc *tool)
{
	int		nbr_line;

	if (tool->nbr_char >= TC_SIZE - 2)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else
	{
		ft_clear_all_lines(tool);
		ft_add_char(tool, buff[0]);
		tputs(tgetstr("im", NULL), 1, ft_termput);
		write(1, tool->buff, ft_strlen(tool->buff));
		tputs(tgetstr("ei", NULL), 1, ft_termput);
		ft_replace_cursor(tool);
		ft_adjust_cursor(tool);
		tool->nbr_char++;
		nbr_line = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
		if (nbr_line > tool->y_max + 1)
			tool->y_max = nbr_line - 1;
	}
}

/*void	ft_insert_char(char *buff, t_tc *tool)
{
	int		nbr_line;

	if (tool->nbr_char >= TC_SIZE - 2)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else if (buff[0] == 'c')
		ft_clear_all_lines(tool);
	else
	{
		//tputs(tgetstr("sc", NULL), 1, ft_termput);
		ft_clear_all_lines(tool);
		ft_add_char(tool, buff[0]);
		tputs(tgetstr("im", NULL), 1, ft_termput);
		write(1, tool->buff, ft_strlen(tool->buff));
		tputs(tgetstr("ei", NULL), 1, ft_termput);
		tool->curs_x++;
		//tputs(tgetstr("rc", NULL), 1, ft_termput);
		if (tool->curs_x > tool->x_max)
		{
			tool->curs_x = 0;
			tool->curs_y++;
			tputs(tgetstr("do", NULL), 1, ft_termput);
			tputs(tgetstr("cr", NULL), 1, ft_termput);
			//if (tool->curs_y > tool->y_max)
			//	tool->y_max++;
		}
		else
		{
			tputs(tgetstr("nd", NULL), 1, ft_termput);
		}	
		tool->nbr_char++;
		nbr_line = (tool->nbr_char + tool->prompt_len) / (tool->x_max + 1);
		if (nbr_line > tool->y_max + 1)
		{
			//tputs(tgetstr("up", NULL), 1, ft_termput);
			tool->y_max = nbr_line - 1;
		}
	}
}*/

void	ft_go_to_eol(t_tc *tool)
{
	int		i;

	i = tool->curs_x;
	while (i < tool->x_max)
	{
		tputs(tgetstr("nd", NULL), 1, ft_termput);
		i++;
	}
	tool->curs_x = tool->x_max;
}

void	ft_move_left(t_tc *tool)
{
	if (tool->curs_y == 0 && tool->curs_x == tool->prompt_len)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else if (tool->curs_x != 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_termput);
		tool->curs_x--;
	}
	else if (tool->curs_x == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_termput);
		tool->curs_y--;
		ft_go_to_eol(tool);
	}
}

void	ft_move_right(t_tc *tool)
{
	if (tool->curs_y * (tool->x_max + 1) + tool->curs_x + 1 == tool->nbr_char + tool->prompt_len + 1)
		tputs(tgetstr("bl", NULL), 1, ft_termput);
	else if (tool->curs_x == tool->x_max)
	{
		tputs(tgetstr("do", NULL), 1, ft_termput);
		tputs(tgetstr("cr", NULL), 1, ft_termput);
		tool->curs_y++;
		tool->curs_x = 0;
	}
	else
	{
		tputs(tgetstr("nd", NULL), 1, ft_termput);
		tool->curs_x++;
	}
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
}

void	ft_buff_analysis(char *buff, t_tc *tool)
{
	if (buff[0] == '\n')
		ft_insert_eol(tool);
	if (ft_isprint(buff[0]) == 1)
		ft_insert_char(buff, tool);
	if (buff[0] == 27 && buff[2] == 68)
		ft_move_left(tool);
	if (buff[0] == 27 && buff[2] == 67)
		ft_move_right(tool);
}

void	ft_put_prompt(void)
{
	write(1, "PROMPT $> ", 10);
}

int		main(void)
{
	t_tc	tool;
	char	little_buff[5];
	int		stop = 0;
	int		prompt_len = ft_strlen("PROMPT $> ");

	ft_put_prompt();
	ft_init_tc();
	ft_init_struct_tc(&tool, prompt_len);
	while (stop == 0)
	{
		ft_bzero(little_buff, 5);
		read(0, little_buff, 5);

		//ft_putendl("");
		//ft_putnbr2("buff0 = ", little_buff[0]);
		//ft_putnbr2("buff1 = ", little_buff[1]);
		//ft_putnbr2("buff2 = ", little_buff[2]);

		ft_buff_analysis(little_buff, &tool);
		if (little_buff[0] == '\n')
		{
			stop = 1;
			ft_putendl("");
			ft_putendl2_fd("tool->buff = ", tool.buff, 1);
			ft_putnbr2("x_max = ", tool.x_max);
			ft_putnbr2("y_max = ", tool.y_max);
			ft_putnbr2("curs_x = ", tool.curs_x);
			ft_putnbr2("curs_y = ", tool.curs_y);
			ft_putnbr2("nbr_char = ", tool.nbr_char);
		}
	}
	ft_reset_tc();
	return (0);
}
