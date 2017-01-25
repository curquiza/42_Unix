#include "ft_ls.h"
#include "libft.h"

int		ft_print_indir(char *filename)
{
	DIR				*dirp;
	struct dirent	*ret_read;

	if (!(dirp = opendir(filename)))
		return (-1);
	ft_putstr(filename);
	ft_putendl(":");
	while ((ret_read = readdir(dirp)))
		ft_putendl(ret_read->d_name);
	if (closedir(dirp) != 0)
		return (-1);
	return (0);
}

void	ft_print_alldir(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac == 1) //faux si options
	{
		av[1] = ft_strdup(".");
		ac = 2;
	}
	while (i < ac)
	{
		if (ft_print_indir(av[i]) == -1)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd(": ", 2);
			perror("");
		}
		if (i != ac - 1)
			ft_putchar('\n');
		i++;
	}
}
