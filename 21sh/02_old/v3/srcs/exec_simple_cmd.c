/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:37:13 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/15 18:23:46 by curquiza         ###   ########.fr       */
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

int		ft_fork_and_exec(t_ast *ast, t_var *vartab)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		ft_put_errmsg("21sh", NULL, "fork error");
	if (pid == 0)
	{
		if (execve(ast->cmd->s, ast->argtab, vartab->env) == -1)
			exit(0);
	}
	else if (pid > 0)
	{
		wait(&pid);
	}
	return (0);
}

int		ft_exec_simple_cmd(t_ast *ast, t_var *vartab)
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
		return (ft_fork_and_exec(ast, vartab));
	}
	return (0);
}
