#include "ft_ls.h"

int		ft_list_filenames(char *filename)
{
	DIR				*dirp;
	struct dirent	*ret_read;

	if (!(dirp = opendir(filename)))
	{
		//printf("errno = %d\n", errno);
		//printf("strerror = %s\n", strerror(errno));
		perror("opendir");
		return (-1);
	}
	while ((ret_read = readdir(dirp)) != NULL)
	{
		ft_putendl(ret_read->d_name);
		//printf("type file : %hhu\n", ret_read->d_type);
	}
	if (closedir(dirp) < 0)
		return (-1);
	return (0);
}

int		ft_printinfo_dir(char *path, struct stat *info_dir)
{
	struct passwd	*pwd;
	struct group	*grp;

	if (lstat(path, info_dir) == -1)
	{
		//printf("errno = %d\n", errno);
		//printf("strerror = %s\n", strerror(errno));
		perror("stat");
		return (-1);
	}
	//printf("ID de l'appareil contenant le file : %d\n", info_dir->st_dev);
	printf("Nombre de liens : %hu\n", info_dir->st_nlink);
	//printf("Num de fichier : %llu\n", info_dir->st_ino);
	//printf("ID de l'appareil : %d\n", info_dir->st_rdev);
	//printf("date dernier acces : \t\t%s", ctime(&(info_dir->st_atimespec.tv_sec)));
	//printf("date dernier acces : %ld\n", info_dir->st_atimespec.tv_sec);
	printf("date derniere modif : %s", ctime(&(info_dir->st_mtimespec.tv_sec)));
	printf("date derniere modif (en sec) : %ld\n", info_dir->st_mtimespec.tv_sec);
	printf("date derniere modif (en nanosec) : %ld\n", info_dir->st_mtimespec.tv_nsec);
	//printf("date dernier chgmt statut : \t%s", ctime(&(info_dir->st_ctimespec.tv_sec)));
	//printf("date dernier chgmt statut : \t%ld\n", info_dir->st_ctimespec.tv_sec);
	//printf("date creation : \t\t%s", ctime(&(info_dir->st_birthtimespec.tv_sec)));
	//printf("date creation : \t\t%ld\n", info_dir->st_birthtimespec.tv_sec);
	printf("size : %lld\n", info_dir->st_size);
	//printf("Nbr de blocks alloués : %lld\n", info_dir->st_blocks);
	//printf("Nbr de blocks alloués optimal : %d\n", info_dir->st_blksize);
	//printf("Flags : %u\n", info_dir->st_flags);
	//printf("Nbr genereation du file : %u\n", info_dir->st_gen);

	printf("\nMode en base 10 : %d\n", info_dir->st_mode);
	printf("Mode en base 8 : %s\n", ft_itoa_base(info_dir->st_mode, 8));
	if (S_ISLNK(info_dir->st_mode))
		printf("Type de file : lien symbolique\n");
	if (S_ISREG(info_dir->st_mode))
		printf("Type de file : fichier régulier\n");
	if (S_ISDIR(info_dir->st_mode))
		printf("Type de file : répertoire\n");
	if (S_ISBLK(info_dir->st_mode))
		printf("Type de file : périphérique en mode bloc\n");
	if (S_ISFIFO(info_dir->st_mode))
		printf("Type de file : FIFO\n");
	if (S_ISSOCK(info_dir->st_mode))
		printf("Type de file : socket\n");
	if (S_ISCHR(info_dir->st_mode))
		printf("Type de file : périphérique en mode caractère\n");
	
	printf("Droits : ");
	if ((info_dir->st_mode & S_IRUSR) == S_IRUSR)
		printf("r");
	else
		printf("-");
	if ((info_dir->st_mode & S_IWUSR) == S_IWUSR)
		printf("w");
	else
		printf("-");
	if ((info_dir->st_mode & S_IXUSR) == S_IXUSR)
		printf("x");
	else
		printf("-");
	if ((info_dir->st_mode & S_IRGRP) == S_IRGRP)
		printf("r");
	else
		printf("-");
	if ((info_dir->st_mode & S_IWGRP) == S_IWGRP)
		printf("w");
	else
		printf("-");
	if ((info_dir->st_mode & S_IXGRP) == S_IXGRP)
		printf("x");
	else
		printf("-");
	if ((info_dir->st_mode & S_IROTH) == S_IROTH)
		printf("r");
	else
		printf("-");
	if ((info_dir->st_mode & S_IWOTH) == S_IWOTH)
		printf("w");
	else
		printf("-");
	if ((info_dir->st_mode & S_IXOTH) == S_IXOTH)
		printf("x");
	else
		printf("-");
	printf("\n");
	
	printf("\nID de l'user : %u\n", info_dir->st_uid);
	pwd = getpwuid(info_dir->st_uid);
	printf("user name : %s\n", pwd->pw_name);
	/*printf("user pwd : %s\n", pwd->pw_passwd);
	//printf("user uid  : %d\n", pwd->pw_uid);
	//printf("user gid  : %d\n", pwd->pw_gid);
	printf("access user class : %s\n", pwd->pw_class);
	printf("user home : %s\n", pwd->pw_dir);
	printf("user shell : %s\n", pwd->pw_shell);
	printf("user Honeywell : %s\n", pwd->pw_gecos);
	printf("expire : %s\n", ctime(&(pwd->pw_expire)));
	//printf("fields : %d\n", pwd->pw_fields);*/
	
	printf("ID du groupe : %u\n", info_dir->st_gid);
	grp = getgrgid(info_dir->st_gid);
	printf("nom du groupe : %s\n", grp->gr_name);
	/*printf("password du groupe : %s\n", grp->gr_passwd);
	//printf("ID du groupe : %u\n", grp->gr_gid);
	printf("membres du groupe : %s\n", grp->gr_mem[0]);
	printf("membres du groupe : %s\n", grp->gr_mem[1]);*/
	return (0);
}

int		main(int ac, char **av)
{
	struct stat		stat_dir;

	if (ac != 2)
		return (0);
	ft_list_filenames(av[1]);
	//if (ft_list_filenames(av[1]) != 0)
		//ft_putendl("ERROR read");
	ft_putendl("");
	ft_printinfo_dir(av[1], &stat_dir);
	//if (ft_printinfo_dir(av[1], &stat_dir) != 0)
	//	ft_putendl("ERROR stat");
	return (0);
}
