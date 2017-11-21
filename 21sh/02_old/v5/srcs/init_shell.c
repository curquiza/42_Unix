/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 23:01:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:59:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*ft_init_shell(char **environ)
{
	t_shell		*shell;

	if (!(shell = (t_shell *)malloc(sizeof(*shell))))
		ft_exit("malloc error", 1);
	shell->var_env = ft_init_env(environ);
	shell->var_loc = NULL;
	shell->var_priv = ft_init_priv();
	shell->run = 1;
	shell->exit_status = 0;
	return (shell);
}

char	**ft_init_priv(void)
{
	char	**priv;

	priv = NULL;
	ft_add_var(&priv, "?", "0");
	return (priv);
}

char	**ft_init_env(char **environ)
{
	char	**env;
	char	*charval;
	int		intval;
	char	*pwd;

	env = ft_tabdup(environ);
	intval = 0;
	charval = ft_get_varvalue(env, "SHLVL");
	if (charval)
		intval = ft_atoi(charval);
	intval++;
	charval = ft_itoa(intval);
	ft_chg_varval_or_add(&env, "SHLVL", charval);
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_chg_varval_or_add(&env, "PWD", pwd);
	else
		ft_chg_varval_or_add(&env, "PWD", "");
	free(pwd);
	free(charval);
	return (env);
}
