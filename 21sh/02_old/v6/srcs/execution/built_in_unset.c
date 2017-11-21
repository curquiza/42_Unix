#include "shell.h"

int				ft_builtin_unset(t_ast *ast)
{
	int		i;
	int		ret;

	if (ast->argtab && !ast->argtab[1])
	{
		ft_put_errmsg(ast->shell->name, ast->argtab[0], "too few arguments");
		return (CMD_FAILURE);
	}
	ret = CMD_SUCCESS;
	i = -1;
	while (ast->argtab && ast->argtab[++i])
	{
		if (ft_get_varvalue(ast->shell->var_priv, ast->argtab[i]))
		{
			ft_put_readonly_errmsg(ast->shell->name, ast->argtab[0],
														ast->argtab[i]);
			ret = CMD_FAILURE;
		}
		else
		{
			ft_suppr_var(&ast->shell->var_loc, ast->argtab[i]);
			ft_suppr_var(&ast->shell->var_env, ast->argtab[i]);
		}
		//i++;
	}
	return (ret);
}
