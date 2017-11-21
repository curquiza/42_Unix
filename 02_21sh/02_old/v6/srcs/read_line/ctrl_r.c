#include "shell.h"

void	ft_ctrl_r(t_tc *tool)
{
	ft_putendl("");
	ft_putstr(HISTO_S_PROMPT);
	ft_init_struct_tc(tool, ft_strlen(HISTO_S_PROMPT));
	tool->ctrl_r = 1;
}

char	*ft_histo_matches(char *buff, t_histo *histo)
{
	if (!histo)
		return (NULL);
	while (histo)
	{
		if (ft_strstr(histo->line, buff) != NULL)
		{
			return (histo->line);
			break;
		}
		histo = histo->next;
	}
	return (NULL);
}

void	ft_put_ctrl_r_rslt(t_tc *tool, t_histo_ctrl *ctrl)
{
	char	*rslt;

	rslt = ft_histo_matches(tool->buff, ctrl->start);
	if (rslt == NULL)
	{
		ft_putendl("");
		ft_putstr(HISTO_ERR_MSG);
		ft_fill_cmd_return(1, g_shell);
	}
	else
	{
		ft_putendl("");
		ft_putstr(HISTO_OK_MSG);
		ft_fill_cmd_return(0, g_shell);
	}
	ft_putendl("\n");
	ft_put_prompt();
	ft_init_struct_tc(tool, PROMPT_DEF_SIZE);
	if (rslt)
		ft_insert(rslt, tool);
}
