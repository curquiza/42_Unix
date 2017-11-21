/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:57:10 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/04 18:12:34 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lexeme	*ft_lexlst_new(char *s)
{
	t_lexeme	*new;

	if (!(new = (t_lexeme *)malloc(sizeof(*new))))
		ft_exit("malloc error", 1);
	if (s == NULL)
		new->s = NULL;
	else
		new->s = ft_strdup(s);
	new->hdoc = NULL;
	new->token = 0;
	new->op = 0;
	new->next = NULL;
	return (new);
}

void		ft_lexlst_addback(t_lexeme **alst, t_lexeme *new)
{
	t_lexeme	*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_lexeme	*ft_lexlst_last(t_lexeme *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		ft_lexlst_len(t_lexeme *lst)
{
	int		cpt;

	cpt = 0;
	while (lst)
	{
		cpt++;
		lst = lst->next;
	}
	return (cpt);
}

void	ft_lex_suppr_elem(t_lexeme **elem)
{
	t_lexeme	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_strdel(&suppr->s);
	ft_strdel(&suppr->hdoc);
	suppr->next = NULL;
	free(suppr);
}

void	ft_lexlst_remove_if(t_lexeme **begin_list, void *ref, int mode)
{
	t_lexeme	*current;

	if (*begin_list)
	{
		current = *begin_list;
		while (current->next)
		{
			if (mode == 0 && ft_strcmp(current->next->s, ref) == 0)
				ft_lex_suppr_elem(&(current->next));
            else if (mode == 1 && current->next->token == *(int *)ref)
				ft_lex_suppr_elem(&(current->next));
			else
				current = current->next;
		}
		if (*begin_list)
		{
			if (mode == 0 && ft_strcmp((*begin_list)->s, ref) == 0)
				ft_lex_suppr_elem(begin_list);
            else if (mode == 1 && (*begin_list)->token == *(int *)ref)
				ft_lex_suppr_elem(begin_list);
		}
	}
}

void	ft_lexlstdel(t_lexeme **alst)
{
	t_lexeme	*current;

	if (!alst)
		return ;
	current = *alst;
	while (current)
		ft_lex_suppr_elem(&(current));
	*alst = NULL;
}
