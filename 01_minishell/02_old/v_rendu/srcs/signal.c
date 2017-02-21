/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:43 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/17 16:09:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*g_user = NULL;

void	ft_ctrlc_donothing(int sig)
{
	(void)sig;
}

void	ft_ctrlc_prompt(int sig)
{
	(void)sig;
	signal(SIGINT, ft_ctrlc_prompt);
	ft_putchar('\n');
	ft_putprompt_signal(g_user);
}

void	ft_ctrlc_noprompt(int sig)
{
	(void)sig;
	signal(SIGINT, ft_ctrlc_noprompt);
	ft_putchar('\n');
}

void	ft_signal_ctrlc(char **env)
{
	g_user = ft_get_envvar("USER", env) + 5;
	signal(SIGINT, ft_ctrlc_prompt);
}

void	ft_signal_minishell(char *bin)
{
	if (ft_strcmp(bin, "minishell") != 0 && ft_strcmp(bin, "./minishell") != 0)
		signal(SIGINT, ft_ctrlc_noprompt);
	else
		signal(SIGINT, ft_ctrlc_donothing);
}
