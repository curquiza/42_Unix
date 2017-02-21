/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:52:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/10 14:53:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_putprompt(char **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_col(pwd, PROMPT_PWD_COL, DEF);
		ft_putstr_col(" ", PROMPT_PWD_COL, DEF);
	}
	if (ft_exist("USER", env) == 1)
	{
		ft_putstr_col(ft_get_envvar("USER", env) + 5, PROMPT_USR_COL, DEF);
		ft_putstr_col("'s ", PROMPT_USR_COL, DEF);
	}
	ft_putstr_col("minishell $> ", PROMPT_USR_COL, DEF);
	ft_strdel(&pwd);
}

void	ft_putprompt_signal(char *user)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_col(pwd, PROMPT_PWD_COL, DEF);
		ft_putstr_col(" ", PROMPT_PWD_COL, DEF);
	}
	if (user)
	{
		ft_putstr_col(user, PROMPT_USR_COL, DEF);
		ft_putstr_col("'s ", PROMPT_USR_COL, DEF);
	}
	ft_putstr_col("minishell $> ", PROMPT_USR_COL, DEF);
	ft_strdel(&pwd);
}
