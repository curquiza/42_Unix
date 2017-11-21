/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 16:31:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:02:31 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_varvalue(char **vartab, char *varname)
{
	int		len;
	int		varlen;

	if (vartab)
	{
		varlen = ft_strlen(varname);
		while (*vartab)
		{
			len = 0;
			while ((*vartab)[len] && (*vartab)[len] != '=')
				len++;
			if (len == varlen && ft_strncmp(*vartab, varname, len) == 0)
				return (ft_strchr(*vartab, '=') + 1);
			vartab++;
		}
	}
	return (NULL);
}

int		ft_get_varindex(char **vartab, char *varname)
{
	int		len;
	int		index;
	int		varlen;

	if (vartab)
	{
		varlen = ft_strlen(varname);
		index = 0;
		while (vartab[index])
		{
			len = 0;
			while (vartab[index][len] && vartab[index][len] != '=')
				len++;
			if (len == varlen && ft_strncmp(vartab[index], varname, len) == 0)
				return (index);
			index++;
		}
	}
	return (-1);
}

int		ft_exist_in(char **vartab, char *varname)
{
	int		varlen;
	int		len;

	if (vartab)
	{
		varlen = ft_strlen(varname);
		while (*vartab)
		{
			len = 0;
			while ((*vartab)[len] && (*vartab)[len] != '=')
				len++;
			if (varlen == len && ft_strncmp(*vartab, varname, len) == 0)
				return (1);
			vartab++;
		}
	}
	return (0);
}

/*char	**ft_add_var(char ***vartab, char *newvar, char *value)
{
	char	**tmp;
	int		i;

	if (!(tmp = (char **)malloc(sizeof(**vartab) * (ft_tablen(*vartab) + 2))))
		ft_exit("malloc error", 1);
	i = 0;
	while ((*vartab)[i])
	{
		tmp[i] = (*vartab)[i];
		i++;
	}
	if (value == NULL)
		tmp[i] = ft_strdup(newvar);
	else
		tmp[i] = ft_strjoin3(newvar, "=", value);
	tmp[i + 1] = NULL;
	free(*vartab);
	return (tmp);
}*/

void	ft_add_var(char ***vartab, char *newvar, char *value)
{
	char	**tmp;
	int		i;

	if (!(tmp = (char **)malloc(sizeof(**vartab) * (ft_tablen(*vartab) + 2))))
		ft_exit("malloc error", 1);
	i = 0;
	while ((*vartab) && (*vartab)[i])
	{
		tmp[i] = (*vartab)[i];
		i++;
	}
	if (value == NULL)
		tmp[i] = ft_strdup(newvar);
	else
		tmp[i] = ft_strjoin3(newvar, "=", value);
	tmp[i + 1] = NULL;
	free(*vartab);
	*vartab = tmp;
}

void	ft_chg_varval(char **vartab, char *newvar, char *value) 
{
	char	*name;
	int		len;
	int		index;

	if (value == NULL)
	{
		len = 0;
		while (newvar[len] && newvar[len] != '=')
			len++;
		name = ft_strsub(newvar, 0, len);
	}
	else
		name = newvar;
	index = ft_get_varindex(vartab, name);
	free(vartab[index]);
	if (value == NULL)
	{
		vartab[index] = ft_strdup(newvar);
		free(name);
	}
	else
		vartab[index] = ft_strjoin3(newvar, "=", value);
}

void	ft_chg_varval_or_add(char ***vartab, char *newvar, char *value)
{
	int		len;
	char	*tmpvar;

	len = 0;
	if (value == NULL)
	{
		while (newvar[len] && newvar[len] != '=')
			len++;
		tmpvar = ft_strsub(newvar, 0, len);
	}
	else
		tmpvar = newvar;
	if (ft_exist_in(*vartab, tmpvar) == 1)
		ft_chg_varval(*vartab, newvar, value);
	else
		//*vartab = ft_add_var(vartab, newvar, value);
		ft_add_var(vartab, newvar, value);
	if (value == NULL)
		ft_strdel(&tmpvar);
}

void	ft_suppr_var(char ***vartab, char *varname)
{
	int		index;
	char	**tmp;
	int		i;
	int		j;

	if ((index = ft_get_varindex(*vartab, varname)) == -1)
		return ;
	tmp = *vartab;
	if (!(*vartab = (char **)malloc(sizeof(**vartab) * ft_tablen(tmp))))
		ft_exit("malloc error", 1);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (i != index)
		{
			(*vartab)[j] = tmp[i];
			j++;
		}
		i++;
	}
	(*vartab)[j] = NULL;
	ft_strdel(&tmp[index]);
	free(tmp);
}
