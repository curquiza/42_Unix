/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:51:17 by curquiza          #+#    #+#             */
/*   Updated: 2017/02/04 13:04:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** In this file :
** Gets the arguments of the command (= btw two ';')
** arguments = the 2nd parameter (char **) of the function execve
*/

int				ft_countarg(char *s)
{
	int		cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
		{
			cnt++;
			while (*s && *s != ' ' && *s != '\t')
			{
				if (*s == 39 || *s == '"')
					s = ft_strchr(s + 1, *s);
				s++;
			}
		}
		else
			s++;
	}
	return (cnt);
}

int				ft_arglen(char *s)
{
	int		len;
	char	quote;

	len = 0;
	while (*s && *s != ' ' && *s != '\t')
	{
		if (*s != 39 && *s != '"')
			len++;
		else
		{
			quote = *s;
			s++;
			while (*s != quote)
			{
				len++;
				s++;
			}
		}
		s++;
	}
	return (len);
}

char			*ft_get_onearg(char *s)
{
	char	*arg;
	int		i;
	char	quote;

	while (*s == ' ' || *s == '\t')
		s++;
	arg = ft_strnew(ft_arglen(s));
	//printf("arglen = %d\n", ft_arglen(s));
	i = 0;
	while (*s && *s != ' ' && *s != '\t')
	{
		if (*s == 39 || *s == '"')
		{
			quote = *s;
			s++;
			while (*s != quote)
			{
				//arg[i++] = *s++;
				arg[i++] = *s;
				s++;
			}
		}
		else
			arg[i++] = *s;
		s++;
	}
	//printf("arg = \"%s\"\n", arg);
	return (arg);
}

static char		*ft_go_argend(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	while (*s && *s != ' ' && *s != '\t')
	{
		if (*s == 39 || *s == '"')
			s = ft_strchr(s + 1, *s);
		s++;
	}
	return (s);
}

char			**ft_add_arg(char *s, char *bin)
{
	int		i;
	char	**arg;
	int		nb_arg;

	nb_arg = ft_countarg(s);
	if (!(arg = (char **)malloc(sizeof(*arg) * (nb_arg + 1))))
		return (NULL);
	if (ft_strrchr(bin, '/'))
		arg[0] = ft_strdup(ft_strrchr(bin, '/') + 1);
	else
		arg[0] = ft_strdup(bin);
	arg[nb_arg] = NULL;
	if (nb_arg == 1)
		return (arg);
	s = ft_go_argend(s);
	i = 1;
	while (i < nb_arg)
	{
		arg[i] = ft_get_onearg(s);
		i++;
		s = ft_go_argend(s);
	}
	return (arg);
}
