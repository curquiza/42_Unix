#include "shell.h"

int		ft_get_cmdret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		ft_putendl("\n/!\\ /!\\ Processus fils fermé par un signal /!\\ /!\\");
		if (WTERMSIG(status) == SIGSEGV)
			ft_putendl("=> SEGFAULT");
		if (WTERMSIG(status) == SIGABRT)
			ft_putendl("=> SIGABORT");
		else
			ft_putnbr2("signal = ", WTERMSIG(status));
	}
	return (CMD_FAILURE);
}

void	ft_fill_cmd_return(int ret, t_shell *shell)
{
	char	*ret_char;

	ret_char = ft_itoa(ret);
	ft_chg_varval_or_add(&shell->var_priv, "?", ret_char);
	ft_strdel(&ret_char);
}
