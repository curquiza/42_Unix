/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bigr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:23:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/21 11:18:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_sink :
** Déplacements dans l'arborescence et affichage
*/

void	ft_sink(t_path **tab, char *opt, void (**f)(t_path **, char *), int pos)
{
	char	*tmp_display;

	if (!tab || !tab[pos])
		return ;
	tmp_display = ft_name_in_path(tab[pos]->name);
	if (tab[pos]->display == NULL || ft_strcmp(tmp_display, ".") == 0
		|| ft_strcmp(tmp_display, "..") == 0)
	{
		ft_sink(tab, opt, f, pos + 1);
		return ;
	}
	if (tab[pos]->inside == NULL)
		tab[pos]->inside = ft_new_inside(tab[pos], opt);
	if (ft_toopen(tab[pos], opt, 0))
	{
		ft_run(tab[pos]->inside, opt, f);
		ft_putendl("");
		ft_putstr(tab[pos]->name);
		ft_putendl(":");
		//ft_putstr_color(tab[pos]->name, YELLOW_BOLD);
		//ft_putendl_color(":", YELLOW_BOLD);
		ft_print_indir(tab[pos], opt, 0);
		ft_sink(tab[pos]->inside, opt, f, 0);
	}
	ft_sink(tab, opt, f, pos + 1);
}

/*
** ft_opt_bigr :
** Début de l'option R
*/

void	ft_opt_bigr(t_path **argpath, char *opt, void (**f)(t_path **, char *))
{
	int		len;
	int		i;
	int		last;

	len = ft_pathtablen(argpath);
	ft_run(argpath, opt, f);
	ft_print_notdir(argpath, opt);
	i = -1;
	while (argpath[++i])
		ft_toopen(argpath[i], opt, 1) ? last = i : 0;
	i = 0;
	while (argpath[i])
	{
		if (ft_toopen(argpath[i], opt, 1))
		{
			ft_run(argpath[i]->inside, opt, f);
			ft_print_dirpath(argpath[i], len);
			ft_print_indir(argpath[i], opt, 1);
			ft_sink(argpath[i]->inside, opt, f, 0);
		}
		i != last && S_ISDIR(argpath[i]->lstat.st_mode) ? ft_putendl("") : 0;
		i++;
	}
}
