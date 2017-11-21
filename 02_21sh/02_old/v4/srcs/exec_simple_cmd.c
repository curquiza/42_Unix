/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:37:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 19:57:03 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

enum e_cmd_search	ft_check_cmd_slash(t_ast *ast)
{
	int			ret_stat;
	int			ret_access;
	struct stat	buff;
	
	ret_stat = stat(ast->cmd->s, &buff);
	ret_access = access(ast->cmd->s, X_OK);
	if (ret_stat != -1 && S_ISDIR(buff.st_mode))
		return (ISDIR);
	else if (ret_stat != -1 && ret_access == -1)
		return (NOPERM);
	else if (ret_stat == -1)
		return (NOSUCHFILE);
	return (FOUND);
}

char	**ft_get_pathtab(t_var *vartab)
{
	char	*path_str;

	path_str = ft_get_varvalue(vartab->env, "PATH");
	if (!path_str)
		path_str = ft_get_varvalue(vartab->local, "PATH");
	if (!path_str)
		return (NULL);
	return (ft_strsplit(path_str, ':'));
}

enum e_cmd_search	ft_check_path(char *cmd)
{
	int			ret_stat;
	int			ret_access;
	struct stat	buff;

	ret_stat = stat(cmd, &buff);
	ret_access = access(cmd, X_OK);
	if (ret_stat != -1 && ret_access != -1)
		return (FOUND);
	else if (ret_stat != -1 && ret_access == -1)
		return (NOPERM);
	return (0);
}

enum e_cmd_search	ft_check_cmd_noslash(t_ast *ast, t_var *vartab)
{
	char				**path_tab;
	char				*cmd;
	enum e_cmd_search	ret;
	int					i;

	if (!(path_tab = ft_get_pathtab(vartab)))
		return (0);
	cmd = NULL;
	i = 0;
	while (path_tab[i])
	{
		ft_strdel(&cmd);
		cmd = ft_strjoin3(path_tab[i], "/", ast->cmd->s);
		if ((ret = ft_check_path(cmd)) != 0)
			break ;
		i++;
	}
	if (ret == FOUND)
		ft_strdeldup(&ast->cmd->s, cmd);	
	ft_strdel(&cmd);
	ft_tabdel(&path_tab);
	return (ret == 0 ? NOTFOUND : ret);
}

/*int		ft_fork_and_exec(t_ast *ast, t_var *vartab)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	if (ast)
	{
		if ((pid = fork()) == -1)
			ft_put_errmsg("21sh", NULL, "fork error");
		if (pid == 0)
		{
			if (ast->cmd)
				execve(ast->cmd->s, ast->argtab, vartab->env);
			exit(1);
		}
		else if (pid > 0)
			wait(&ret);
	}
	return (ret);
}*/

/*int		ft_load_simple_cmd(t_ast *ast, t_var *vartab)
{
	enum e_cmd_search	error_ret;
	enum e_builtin 		builtin_ret;

	// gerer les ass_word
	// gerer les redir
	if (ast->cmd && ast->cmd->s)
	{
		if (ft_strchr(ast->cmd->s, '/'))
			error_ret = ft_check_cmd_slash(ast);
		else if ((builtin_ret = ft_is_built_in(ast->cmd->s)) != NOT_BUILTIN)
			return (ft_exec_built_in(ast, builtin_ret, vartab));
		else
			error_ret = ft_check_cmd_noslash(ast, vartab);
		if (error_ret != FOUND)
			return (ft_putmsg_cmderr(ast->cmd->s, error_ret));
	}
	return (0);
}*/

int		ft_do_cmd(t_ast *ast, t_var *vartab)
{
	enum e_cmd_search	error_ret;
	enum e_builtin 		builtin_ret;

	if (ast->cmd && ast->cmd->s)
	{
		if (ft_strchr(ast->cmd->s, '/'))
			error_ret = ft_check_cmd_slash(ast);
		else if ((builtin_ret = ft_is_built_in(ast->cmd->s)) != NOT_BUILTIN)
			return (ft_exec_built_in(ast, builtin_ret, vartab));
		else
			error_ret = ft_check_cmd_noslash(ast, vartab);
		if (error_ret != FOUND)
			return (ft_putmsg_cmderr(ast->cmd->s, error_ret));
		execve(ast->cmd->s, ast->argtab, vartab->env);
	}
	return (0);
}

int		ft_is_number(char *s)
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

int		ft_connect(t_redir *redir)
{
	int		fd;
	int		pfd[2];

	if (redir->op == GREATAND || redir->op == LESSAND)
	{
		if (ft_strcmp(redir->output, "-") == 0)
		{
			if (close(redir->io_nbr) == -1)
				ft_put_errmsg("21sh", redir->output, "close error");
		}
		else if (ft_is_number(redir->output) == 0 || !ft_strcmp(redir->output, ""))
		{
			ft_put_errmsg("21sh", redir->output, "ambiguous redirect");
			return (-1);
		}
		else if (dup2(ft_atoi(redir->output), redir->io_nbr) == -1)
		{
			if (errno == EBADF)
				ft_put_errmsg("21sh", redir->output, "Bad file descriptor");
			else
				ft_put_errmsg("21sh", redir->output, "dup error");
			return (-1);
		}
	}
	else if (redir->op == GREAT)
	{
		if ((fd = open(redir->output, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		{
			if (errno == EACCES)
				ft_put_errmsg("21sh", redir->output, "Permission denied");
			else if (errno == ENOENT)
				ft_put_errmsg("21sh", redir->output, "No such file or directory");
			else if (errno == EISDIR)
				ft_put_errmsg("21sh", redir->output, "Is a directory");
			else
				ft_put_errmsg("21sh", redir->output, "open error");
			return (-1);
		}
		if (dup2(fd, redir->io_nbr) == -1)
		{
			if (errno == EBADF)
				ft_put_errmsg("21sh", redir->output, "Bad file descriptor");
			else
				ft_put_errmsg("21sh", redir->output, "dup error");
			return (-1);
		}
	}
	else if (redir->op == DGREAT)
	{
		if ((fd = open(redir->output, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		{
			if (errno == EACCES)
				ft_put_errmsg("21sh", redir->output, "Permission denied");
			else if (errno == ENOENT)
				ft_put_errmsg("21sh", redir->output, "No such file or directory");
			else if (errno == EISDIR)
				ft_put_errmsg("21sh", redir->output, "Is a directory");
			else
				ft_put_errmsg("21sh", redir->output, "open error");
			return (-1);
		}
		if (dup2(fd, redir->io_nbr) == -1)
		{
			if (errno == EBADF)
				ft_put_errmsg("21sh", redir->output, "Bad file descriptor");
			else
				ft_put_errmsg("21sh", redir->output, "dup error");
			return (-1);
		}
	}
	else if (redir->op == LESS)
	{
		if ((fd = open(redir->output, O_RDONLY)) == -1)
		{
			if (errno == EACCES)
				ft_put_errmsg("21sh", redir->output, "Permission denied");
			else if (errno == ENOENT)
				ft_put_errmsg("21sh", redir->output, "No such file or directory");
			else if (errno == EISDIR)
				ft_put_errmsg("21sh", redir->output, "Is a directory");
			else
				ft_put_errmsg("21sh", redir->output, "open error");
			return (-1);
		}
		if (dup2(fd, redir->io_nbr) == -1)
		{
			if (errno == EBADF)
				ft_put_errmsg("21sh", redir->output, "Bad file descriptor");
			else
				ft_put_errmsg("21sh", redir->output, "dup error");
			return (-1);
		}
	}
	else if (redir->op == DLESS)
	{
		if (pipe(pfd) == -1)
		{
			ft_put_errmsg("21sh", redir->output, "pipe error");
			return (-1);
		}
		if (redir->hdoc)
			write(pfd[1], redir->hdoc, ft_strlen(redir->hdoc));
		close(pfd[1]);
		if (dup2(pfd[0], redir->io_nbr) == -1)
		{
			if (errno == EBADF)
				ft_put_errmsg("21sh", redir->output, "Bad file descriptor");
			else
				ft_put_errmsg("21sh", redir->output, "dup error");
			return (-1);
		}
		close(pfd[0]);
	}
	return (0);
}

int		ft_do_redirection(t_redir *redir)
{
	while (redir)
	{
		if (ft_connect(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
	
}

// exec_scmd
//int		ft_exec_scmd_in_pipe(t_ast *ast, t_var *vartab)
int		ft_exec_simple_cmd(t_ast *ast, t_var *vartab)
{
	if (ast)
	{
		//ft_do_ass_word(ast, vartab);
		if (ast->redir_list && ft_do_redirection(ast->redir_list) == -1)
			return (CMD_FAILURE);
		return (ft_do_cmd(ast, vartab));
	}
	return (CMD_SUCCESS);
}

// fork_and_exec_scmd
//int		ft_exec_scmd(t_ast *ast, t_var *vartab)
int		ft_fork_and_exec(t_ast *ast, t_var *vartab)
{
	pid_t	pid;
	int		ret;

	if (ast)
	{
		ret = 0;
		if ((pid = fork()) == -1)
			ft_put_errmsg("21sh", NULL, "fork error");
		else if (pid == 0)
		{
			//if (ast->redir_list && ft_do_redirection(ast->redir_list) == -1)
			//	exit(CMD_FAILURE);
			//exit(ft_do_cmd(ast, vartab));
			exit(ft_exec_simple_cmd(ast, vartab));
		}
		else if (pid > 0)
			wait(&ret);
		return (ret);
	}
	return (CMD_SUCCESS);
}

//int			ft_exec_simple_cmd(t_ast *ast, t_var *vartab, enum e_simple_cmd mode)

/*int		ft_exec_simple_cmd(t_ast *ast, t_var *vartab)
{
	enum e_cmd_search	error_ret;
	enum e_builtin 		builtin_ret;

	if (ast->cmd && ast->cmd->s)
	{
		if (ft_strchr(ast->cmd->s, '/'))
			error_ret = ft_check_cmd_slash(ast);
		else if ((builtin_ret = ft_is_built_in(ast->cmd->s)) != NOT_BUILTIN)
			return (ft_exec_built_in(ast, builtin_ret, vartab));
		else
			error_ret = ft_check_cmd_noslash(ast, vartab);
		if (error_ret != FOUND)
			return (ft_putmsg_cmderr(ast->cmd->s, error_ret));
		return (ft_fork_and_exec(ast, vartab));
	}
	return (0);
}*/
