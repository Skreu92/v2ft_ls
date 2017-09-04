/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 01:18:15 by Etienne           #+#    #+#             */
/*   Updated: 2017/08/05 17:41:15 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				print_size(off_t size)
{
	if (size < 1000000)
		ft_putchar(' ');
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

char				*get_month(int i)
{
	if (i == 0)
		return ("Jan");
	if (i == 1)
		return ("Fev");
	if (i == 2)
		return ("Mar");
	if (i == 3)
		return ("Avr");
	if (i == 4)
		return ("Mai");
	if (i == 5)
		return ("Jun");
	if (i == 6)
		return ("Jul");
	if (i == 7)
		return ("Aug");
	if (i == 8)
		return ("Sep");
	if (i == 9)
		return ("Oct");
	if (i == 10)
		return ("Nov");
	if (i == 11)
		return ("Dec");
	return ("");
}

void				print_date(time_t timer)
{
	struct tm	*tm_info;

	tm_info = localtime(&timer);
	if (tm_info->tm_mday < 10)
		ft_putchar(' ');
	ft_putnbr(tm_info->tm_mday);
	ft_putchar(' ');
	ft_putstr(get_month(tm_info->tm_mon));
	ft_putchar(' ');
	if (tm_info->tm_hour < 10)
		ft_putchar('0');
	ft_putnbr(tm_info->tm_hour);
	ft_putchar(':');
	if (tm_info->tm_min < 10)
		ft_putchar('0');
	ft_putnbr(tm_info->tm_min);
	ft_putchar(' ');
}

void				check_lnk(char *direc, char *file)
{
	DIR				*dirp;
	struct dirent	*dir;
	char			*buf;
	int				end;
	struct stat		tmp;

	dirp = opendir(direc);
	while ((dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dir->d_name, file) == 0)
			if (dir->d_type == DT_LNK &&
				(lstat(JOIN(JOIN(direc, "/"), file), &tmp) == 0))
			{
				buf = (char *)malloc(sizeof(char) * 255);
				end = readlink(JOIN(JOIN(direc, "/"), file), buf, 255);
				buf[end] = '\0';
				ft_putstr(" -> ");
				ft_putstr(buf);
				return ;
			}
	}
}

void				displayf_l(t_file **begin, char *path)
{
	t_file		*file;
	struct stat	info;
	char		*tmp;
	char		*tmp2;

	file = (*begin);
	while (file)
	{
		tmp2 = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp2, file->path);
		if (stat(tmp, &info) == -1)
			lstat(tmp, &info);
		put_st_mod(info.st_mode, file->path, path);
		print_links(info.st_nlink);
		print_user(info.st_uid);
		print_group(info.st_gid);
		print_size(info.st_size);
		print_date(info.st_mtime);
		ft_putstr(file->path);
		check_lnk(path, file->path);
		write(1, "\n", 1);
		file = file->next;
		free(tmp);
		free(tmp2);
	}
}
