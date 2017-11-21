#include "shell.h"

char	**ft_get_new_env(char **arg, char *flags, t_shell *shell)
{
	char	**new_env;
	int		i;

	if (ft_strchr(flags, 'i'))
	{
		if (!(new_env = (char **)malloc(sizeof(**new_env))))
			ft_exit("malloc error", 1);
		new_env[0] = NULL;
	}
	else
		new_env = ft_tabdup(shell->var_env);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			break ;
		ft_chg_varval_or_add(&new_env, arg[i], NULL);
		i++;
	}
	return (new_env);
}	

t_shell		*ft_get_new_shell(char **arg, char *flags, t_shell *old_shell)
{
	t_shell	*new_shell;
	char	**new_env;

	new_env = ft_get_new_env(arg, flags, old_shell);
	if (!(new_shell = (t_shell *)malloc(sizeof(*new_shell))))
		ft_exit("malloc error", 1);
	new_shell->name = ft_strdup("21sh: env");
	new_shell->run = 1;
	new_shell->exit_status = 0;
	new_shell->var_env = ft_tabdup(new_env);
	new_shell->var_loc = NULL;
	new_shell->var_priv = ft_init_priv();
	new_shell->flags = ft_init_flags(0, NULL);
	ft_tabdel(&new_env);
	return (new_shell);
}

void	ft_del_shell(t_shell **shell)
{
	ft_strdel(&(*shell)->name);
	ft_tabdel(&(*shell)->var_env);
	ft_tabdel(&(*shell)->var_loc);
	ft_tabdel(&(*shell)->var_priv);
	free((*shell)->flags);
	free(*shell);
	*shell = NULL;
}

char	**ft_get_utility(char **arg)
{
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			break ;
		i++;
	}
	return (arg + i);
}

int		ft_exec_utility_env(t_shell *shell, char **arg)
{
	char		*line;
	char		*tmp;
	t_lexeme	*lex;
	t_ast		*ast;
	int			ret;

	line = NULL;
	while (*arg)
	{
		tmp = line;
		line = ft_strjoin3(tmp, " ", *arg);
		ft_strdel(&tmp);
		arg++;
	}
	lex = NULL;
	ft_lexer(&lex, line);
	ft_ast(lex, &ast, shell);
	ret = 0;
	if (!ast)
		ft_lexlstdel(&lex);
	else
	{
		ret = ft_execution(ast);
		ft_del_ast(&ast);
	}
	ft_strdel(&line);
	return (ret);
}

int		ft_builtin_env(t_ast *ast)
{
	char	*flags;
	char	**arg;
	int		flag_error;
	t_shell	*new_shell;
	int		ret;

	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "i")) != 0)
	{
		ft_put_usage("env", flag_error, "i");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	new_shell = ft_get_new_shell(arg, flags, ast->shell);
	ret = 0;
	arg = ft_get_utility(arg);
	if (arg && !(*arg))
		ft_puttab(new_shell->var_env);
	else
		ret = ft_exec_utility_env(new_shell, arg);
	ft_del_shell(&new_shell);
	ft_strdel(&flags);
	return (ret != 0 ? CMD_FAILURE : CMD_SUCCESS);
}
