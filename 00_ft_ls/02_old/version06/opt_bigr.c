/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bigr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:23:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/13 13:52:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_sink(t_path **tab, char *opt, void (**f)(t_path **, char *), int pos)
{
	if (!tab)
		return ;
	if (!tab[pos])
		return ;
	if (ft_strcmp(tab[pos]->display, ".") == 0 || ft_strcmp(tab[pos]->display, "..") == 0)
	{
		ft_sink(tab, opt, f, pos + 1);
		return ;
	}
	if (tab[pos]->inside == NULL)
		tab[pos]->inside = ft_new_inside(tab[pos], opt);
	if (tab[pos]->error == EACCES && S_ISDIR(tab[pos]->lstat.st_mode))
	{
		ft_putendl("");
		ft_putstr(tab[pos]->name);
		ft_putendl(":");
		ft_print_erracc(tab[pos]);
	}
	else if (S_ISDIR(tab[pos]->lstat.st_mode))
	{
		ft_run(tab[pos]->inside, opt, f);
		ft_putendl("");
		ft_putstr(tab[pos]->name);
		ft_putendl(":");
		ft_print_indir(tab[pos]);
		ft_sink(tab[pos]->inside, opt, f, 0);
	}
	ft_sink(tab, opt, f, pos + 1);
}

void	ft_opt_bigr(t_path **argpath, char *opt, void (**f)(t_path **, char *))
{
	int		len;
	int		i;
	int		last;

	len = ft_pathtablen(argpath);
	ft_print_notdir(argpath);
	ft_run(argpath, opt, f);
	i = -1;
	while (argpath[++i])
		ft_isdir(argpath[i]) ? last = i : 0;
	i = 0;
	while (argpath[i])
	{
		ft_run(argpath[i]->inside, opt, f);
		ft_print_dirpath(argpath[i], len);
		ft_print_erracc(argpath[i]);
		ft_print_indir(argpath[i]);
		ft_sink(argpath[i]->inside, opt, f, 0);
		i != last && S_ISDIR(argpath[i]->lstat.st_mode) ? ft_putendl("") : 0;
		//ft_putendl("yop");
		i++;
	}
}
