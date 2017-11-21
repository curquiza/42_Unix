/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:12:46 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/05 21:59:54 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_replace_parameter(char **s, int *i, int len, t_var *tabvar)
{
	char 	*name;
	char	*value;
	char	*tmp;
	int		value_len;
	int		name_len;

	name = ft_strsub(*s, *i + 1, len);
	if (!(value = ft_get_varvalue(tabvar->env, name))
		&& !(value = ft_get_varvalue(tabvar->local, name)))
		value = ft_strdup("");
	else
		value = ft_strdup(value);
	value_len = ft_strlen(value);
	name_len = ft_strlen(name);
	tmp = *s;
	*s = ft_strnew(ft_strlen(tmp) - (name_len + 1) + value_len);
	ft_strncpy(*s, tmp, *i);
	ft_strncpy(*s + *i, value, value_len);
	ft_strcpy(*s + *i + value_len, tmp + *i + 1 + name_len);
	free(tmp);
	free(name);
	free(value);
	*i = *i + value_len;
}

void	ft_parameter_expansion(char **s, t_var *tabvar)
{
	int		i;
	int		len;

	if (!*s)
		return ;
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 92)
			i++;
		else if ((*s)[i] == 39)
			i = ft_next_squote(i, *s);
		else if ((*s)[i] == '$' && ft_isdigit((*s)[i + 1]) == 1)
			ft_replace_parameter(s, &i, 1, tabvar);
		else if ((*s)[i] == '$' && (*s)[i + 1] && (*s)[i + 1] != '\n'
								&& !ft_is_separator((*s)[i + 1]))
		{
			len = 0;
			while ((*s)[i + 1 + len] == '_' || ft_isalnum((*s)[i + 1 + len]))
				len++;
			ft_replace_parameter(s, &i, len, tabvar);
		}
		if ((*s)[i])
			i++;
	}
}
