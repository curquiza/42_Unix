/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:12:41 by curquiza          #+#    #+#             */
/*   Updated: 2017/01/20 17:04:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"



void	ft_print_pathtab(t_path **tab)
{

	if (!tab)
		return ;
	while (*tab)
	{
		printf("name = %s\n", (*tab)->name);
		printf("display = %s\n", (*tab)->display);
		printf("error = %d\n", (*tab)->error);
		printf("date modif lstat : %s", ctime(&(*tab)->lstat.st_mtimespec.tv_sec));
		//printf("date modif lstat nsec : %ld", (*tab)->lstat.st_mtimespec.tv_nsec);
		printf("date modif stat : %s", ctime(&(*tab)->stat.st_mtimespec.tv_sec));
		printf("size : lstat = %lld ", (*tab)->lstat.st_size);
		printf("size stat = %lld", (*tab)->stat.st_size);
		
		printf("lst_in :\n");
		t_list	*current;
		current = (*tab)->lst_in;
		/*int		i;
		while (current)
		{
			printf("%s\n", current->content);
			current = current->next;
		}
		printf("insides->name :\n");
		i = 0;
		if ((*tab)->inside)
		{
			while (((*tab)->inside)[i])
			{
				printf("%s\n", (((*tab)->inside)[i])->name);
				i++;
			}
		}*/
		printf("\n");
		tab++;
	}
}

int		main(int ac, char **av)
{
	char	opt[128];
	t_path	**argpath;
	void	(*f[4])(t_path **, char *);

	ft_start(ac, av, &argpath, opt);
	ft_init_fcttab(f);
	ft_display(argpath, opt, f);
	
	//while (1){}
	//ft_putendl("------------------------");ft_putendl("------------------------");ft_print_pathtab(argpath);

	return (0);
}
