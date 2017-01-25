/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:54:51 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/02 10:54:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** ft_init_opt :
** Initialise le tableau des options avec des zéros
*/

void	ft_init_opt(char *opt)
{
	int		i;

	i = 0;
	while (i < 128)
	{
		opt[i] = 0;
		i++;
	}
}

/*
** ft_parse_optarg :
** Sous fonction de ft_fill_option. Parcourt la chaine de caractère passée en
** paramètre.
** Retourne -1 + affiche l'erreur si illegal option
** Sinon, remplit le tableau opt et retourne 0.
*/

int		ft_parse_optarg(char *opt, char *s)
{
	s++;
	while (*s)
	{
		if (*s != 'R' && *s != 'a' && *s != 'l' && *s != 'r' && *s != 't')
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putchar_fd(*s, 2);
			ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
			return (-1);
		}
		opt[(int)*s] = 1;
		s++;
	}
	return (0);
}

/*
** ft_fill_opt :
** Remplit les options. S'arrête quqnd il n'y a plus d'options à lire.
** Retourne -1 si illegal option, 0 sinon.
*/

int		ft_fill_opt(char *opt, int ac, char **av)
{
	int			i;

	i = 1;
	ft_init_opt(opt);
	while (i < ac)
	{
		if (ft_strcmp("--", av[i]) == 0 || ft_strcmp("-", av[i]) == 0)
			return (0);
		if (av[i][0] == '-')
		{
			if (ft_parse_optarg(opt, av[i]) == -1)
				return (-1);
		}
		else
			return (0);
		i++;
	}
	return (0);
}
