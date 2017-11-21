/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:39:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/15 15:29:04 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_errmsg(char *bin, char *s, char *msg)
{
	ft_putstr_fd(bin, 2);
	ft_putstr_fd(": ", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

int		ft_putmsg_cmderr(char *cmd, enum e_cmd_search ret)
{
	if (ret == NOTFOUND)
	{
		ft_put_errmsg("21sh", cmd, "command not found");
		return (127);
	}
	else if (ret == NOSUCHFILE)
	{
		ft_put_errmsg("21sh", cmd, "no such file or directory");
		return (127);
	}
	else if (ret == NOPERM)
	{
		ft_put_errmsg("21sh", cmd, "permission denied");
		return (126);
	}
	else if (ret == ISDIR)
	{
		ft_put_errmsg("21sh", cmd, "is a directory");
		return (126);
	}
	return (0);
}

