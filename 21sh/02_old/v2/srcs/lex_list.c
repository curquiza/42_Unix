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
//	else if (*s == '\n')
//		new->s = ft_strdup("newline");
	else
		new->s = ft_strdup(s);
	new->hdoc = NULL;

/*	new->esc = NULL;
	if (s)
		new->esc = ft_strnew(ft_strlen(s));*/

	new->token = 0;
	new->op = 0;
/*	new->token = 0;
	if (ind_ionbr != 0)
		new->token = IO_NBR;
	if (*s == '\n')
		new->token = NEWLINE;
	new->op = 0;
	ft_check_c_op(new);
	ft_check_r_op(new);
//	ft_check_name(new); //trop tot car peut etre un NAME sans le '\'*/

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

void	ft_lex_suppr_elem(t_lexeme **elem)
{
	t_lexeme	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_strdel(&suppr->s);
	ft_strdel(&suppr->hdoc);
//	ft_strdel(&suppr->esc);
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

/*void	ft_lexlst_remove_if(t_lexeme **begin_list, void *data_ref, int (*cmp)())
{
	t_lexeme	*current;

	if (*begin_list != 0)
	{
		current = *begin_list;
		while (current->next != 0)
		{
			if ((*cmp)(current->next->s, data_ref) == 0)
				ft_lex_suppr_elem(&(current->next));
			else
				current = current->next;
		}
		if (*begin_list != 0)
		{
			if ((*cmp)((*begin_list)->s, data_ref) == 0)
				ft_lex_suppr_elem(begin_list);
		}
	}
}*/

void	ft_lexlstdel(t_lexeme **alst)
{
	t_lexeme	*current;
	t_lexeme	*suppr;

	if (!alst)
		return ;
	current = *alst;
	suppr = NULL;
	while (current)
		ft_lex_suppr_elem(&(current));
	*alst = NULL;
}
