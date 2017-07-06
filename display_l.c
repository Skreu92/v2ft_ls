/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 01:18:15 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/06 01:18:17 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void put_st_mod(mode_t mode, char *path)
{
	(void)path;
	(mode & S_IFDIR) ? ft_putchar('d') : ft_putchar('-');
	mode = mode & ~S_IFMT;
	(mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

void print_links(nlink_t link)
{
	ft_putchar(' ');
	if (link < 100)
		ft_putchar(' ');
	if (link < 10)
		ft_putchar(' ');
	ft_putnbr(link);
	ft_putchar(' ');
}

void print_user(uid_t user)
{
	ft_putstr((getpwuid(user))->pw_name);
	ft_putchar(' ');
}

void print_group(gid_t group)
{
	ft_putchar(' ');
	ft_putstr(((getgrgid(group)))->gr_name);
	ft_putchar(' ');
} 

void print_size(off_t size)
{
	if (size < 100000)
		ft_putchar(' ');
	if (size < 10000)
		ft_putchar(' ');
	if (size < 1000)
		ft_putchar(' ');
	if (size < 100)
		ft_putchar(' ');
	if (size < 10)
		ft_putchar(' ');
	ft_putnbr(size);
	ft_putchar(' ');
}

char *get_month(int i)
{
	if (i == 0)
		return ("jan");
	if (i == 1)
		return ("fev");
	if (i == 2)
		return ("mar");
	if (i == 3)
		return ("avr");
	if (i == 4)
		return ("mai");
	if (i == 5)
		return ("jun");
	if (i == 6)
		return ("jul");
	if (i == 7)
		return ("aug");
	if (i == 8)
		return ("sep");
	if (i == 9)
		return ("oct");
	if (i == 10 )
		return ("nov");
	if (i == 11)
		return ("dec");
	return ("");
}

void print_date(time_t timer)
{
	struct tm* tm_info;

	tm_info = localtime(&timer);
	ft_putchar(' ');
	ft_putnbr(tm_info->tm_mday);
	ft_putchar(' ');
	ft_putstr(get_month(tm_info->tm_mon));
	ft_putchar(' ');
	if( tm_info->tm_hour < 10)
		ft_putchar('0');
	ft_putnbr(tm_info->tm_hour);
	ft_putchar(':');
	if( tm_info->tm_min < 10)
		ft_putchar('0');
	ft_putnbr(tm_info->tm_min);
	ft_putchar(' ');
}

void displayf_l(t_file **begin)
{
	t_file *file;
	struct stat info;

	file = (*begin);
	while (file)
	{
		stat(file->path, &info);
		put_st_mod(info.st_mode, file->path);
		print_links(info.st_nlink);
		print_user(info.st_uid);
		print_group(info.st_gid);
		print_size(info.st_size);
		print_date(info.st_mtime);
		ft_putstr(file->path);
		write(1, "\n", 1);
		file = file->next;
	}	
}
