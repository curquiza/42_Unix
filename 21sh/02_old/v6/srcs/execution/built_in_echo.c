# include "shell.h"

int				ft_builtin_echo(t_ast *ast)
{
	int		i;
	int		nbr_arg;
	char	**arg;
	char	flag_error;
	char	*flags;

	flags = ft_get_flags(ast->argtab + 1);
	flag_error = ft_check_illegal_flags(flags, "n");
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	nbr_arg = ft_tablen(arg);
	i = 0;
	while (arg[i])
	{
		ft_putstr(arg[i]);
		if (i != nbr_arg - 1)
			ft_putchar(' ');
		i++;
	}
	if (!ft_strchr(flags, 'n'))
		ft_putchar('\n');
	ft_strdel(&flags);
	return (CMD_SUCCESS);
}
