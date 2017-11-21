#include "shell.h"

/*
** Not proud.
*/

void	ft_swap_middle(t_comp *prev)
{
	t_comp	*current;
	t_comp	*tmp;
	t_comp	*next;

	if (!prev)
		return ;
	current = prev->next;
	tmp = current->next;
	next = current->next->next;
	if (prev)
		prev->next = tmp;
	tmp->prev = prev;
	current->next = next;
	if (next)
		next->prev = current;
	tmp->next = current;
	current->prev = tmp;
}

void	ft_swap_beginning(t_comp **comp)
{
	t_comp		*tmp;
	t_comp		*current;
	t_comp		*next;
	
	current = *comp;
	tmp = current->next;
	next = current->next->next;
	tmp->prev = NULL;
	*comp = tmp;
	current->next = next;
	if (next)
		next->prev = current;
	tmp->next = current;
}

void	ft_ascii_sort_words(t_comp **comp)
{
	t_comp		*current;

	if (!*comp || !(*comp)->next)
		return ;
	current = *comp;
	if (ft_strcmp((*comp)->word, (*comp)->next->word) > 0)
		ft_swap_beginning(comp);
	while (current && current->next)
	{
		if (ft_strcmp(current->word, current->next->word) > 0)
		{
			ft_swap_middle(current->prev);
			ft_ascii_sort_words(comp);
			return ;
		}
		current = current->next;
	}
}

/*void	ft_ascii_sort_words(t_comp **comp)
{
	t_comp		*tmp;
	t_comp		*current;
	t_comp		*prev;
	t_comp		*next;

	if (!(*comp)->next)
		return ;
	current = *comp;
	if (ft_strcmp((*comp)->word, (*comp)->next->word) > 0)
	{
		tmp = current->next;
		next = current->next->next;

		tmp->prev = NULL;
		*comp = tmp;
		
		current->next = next;
		if (next)
			next->prev = current;

		tmp->next = current;
	}
	while (current->next)
	{
		if (ft_strcmp(current->word, current->next->word) > 0)
		{
			prev = current->prev;
			next = current->next->next;
			tmp = current->next;

			if (prev)
				prev->next = tmp;
			tmp->prev = prev;
			
			current->next = next;
			if (next)
				next->prev = current;

			tmp->next = current;
			current->prev = tmp;
			ft_ascii_sort_words(comp);
			return ;
		}
		current = current->next;
	}
}*/
