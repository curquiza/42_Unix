/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 22:34:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 22:54:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_connect_fd(char *output, int to, int from)
{
	if (dup2(to, from) == -1)
	{
		if (errno == EBADF)
			ft_put_errmsg("21sh", output, "Bad file descriptor");
		else
			ft_put_errmsg("21sh", output, "dup error");
		return (-1);
	}
	return (0);
}

int		ft_create_file(enum e_op op, char *output)
{
	int		fd;

	fd = 0;
	if (op == GREAT)
		fd = open(output, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (op == LESS)
		fd = open(output, O_RDONLY);
	else if (op == DGREAT)
		fd = open(output, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_put_errmsg("21sh", output, "Permission denied");
		else if (errno == ENOENT)
			ft_put_errmsg("21sh", output, "No such file or directory");
		else if (errno == EISDIR)
			ft_put_errmsg("21sh", output, "Is a directory");
		else
			ft_put_errmsg("21sh", output, "open error");
		return (-1);
	}
	return (fd);
}

int		ft_is_uns_nbr(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (ft_isdigit(*s) == 0)
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

int		ft_apply_fd_aggr(t_redir *redir)
{
	if (ft_strcmp(redir->output, "-") == 0)
	{
		if (close(redir->io_nbr) == -1)
		{
			ft_put_errmsg("21sh", redir->output, "close error");
			return (-1);
		}
	}
	else if (ft_is_uns_nbr(redir->output) == 0 || !ft_strcmp(redir->output, ""))
	{
		ft_put_errmsg("21sh", redir->output, "ambiguous redirect");
		return (-1);
	}
	return (ft_connect_fd(redir->output, ft_atoi(redir->output), redir->io_nbr));
}

/*
** ft_apply_hdoc :
** À l'execution. Gère les here-doc.
** Retourne -1 si erreur, 0 sinon.
*/

int		ft_apply_hdoc(t_redir *redir)
{
	int		ret;
	int		pfd[2];

	if (pipe(pfd) == -1)
	{
		ft_put_errmsg("21sh", redir->output, "pipe error");
		return (-1);
	}
	if (redir->hdoc)
		write(pfd[1], redir->hdoc, ft_strlen(redir->hdoc));
	close(pfd[1]);
	ret = ft_connect_fd(redir->output, pfd[0], redir->io_nbr);
	close(pfd[0]);
	return (ret);
}

int		ft_do_redirection(t_redir *redir)
{
	int		ret;
	int		fd;

	while (redir)
	{
		if (redir->op == GREATAND || redir->op == LESSAND)
			ret = ft_apply_fd_aggr(redir);
		else if (redir->op == DLESS)
			ret = ft_apply_hdoc(redir);
		else
		{
			fd = ft_create_file(redir->op, redir->output);
			ret = -1;
			if (fd != -1)
				ret = ft_connect_fd(redir->output, fd, redir->io_nbr);
		}
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
