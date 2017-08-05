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

void			print_acl(mode_t mode, char *path)
{
	ssize_t		buflen;
	acl_t		a;

	buflen = (S_ISLNK(mode)) ? (listxattr(path, (char*)NULL, 0, XATTR_NOFOLLOW)) : (listxattr(path, (char*)NULL, 0, 0));
	a = (S_ISLNK(mode)) ? (acl_get_link_np(path, ACL_TYPE_EXTENDED)) : (acl_get_file(path, ACL_TYPE_EXTENDED));
	if (buflen > 0)
		ft_putchar('@');
	else if (a != NULL)
		ft_putchar('+');
	else
		ft_putchar(' ');
}

void			put_st_mod(mode_t mode, char *path)
{
	if (S_ISDIR(mode))
		ft_putchar('d');
	else if (S_ISLNK(mode))
		ft_putchar('l');
	else
		ft_putchar('-');
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
	(void)path;
}

void			print_links(nlink_t link)
{
	ft_putchar(' ');
	if (link < 100)
		ft_putchar(' ');
	if (link < 10)
		ft_putchar(' ');
	ft_putnbr(link);
	ft_putchar(' ');
}

void			print_user(uid_t user)
{
	ft_putstr((getpwuid(user))->pw_name);
	ft_putchar(' ');
}

void			print_group(gid_t group)
{
	ft_putchar(' ');
	ft_putstr(((getgrgid(group)))->gr_name);
	ft_putchar(' ');
}

void			print_size(off_t size)
{
	ft_putchar(' ');
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

char			*get_month(int i)
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
	if (i == 10)
		return ("nov");
	if (i == 11)
		return ("dec");
	return ("");
}

void				print_date(time_t timer)
{
	struct tm	*tm_info;

	tm_info = localtime(&timer);
	ft_putchar(' ');
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
		{
			if (dir->d_type == DT_LNK && (lstat(ft_strjoin(ft_strjoin(direc, "/"), file), &tmp) == 0))
			{
				buf = (char *)malloc(sizeof(char) * 255);
				end = readlink(ft_strjoin(ft_strjoin(direc, "/"), file), buf, 255);
				buf[end] = '\0';
				ft_putstr(" -> ");
				ft_putstr(buf);
				return ;
			}
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
		stat(tmp, &info);
		if (stat(tmp, &info) == -1)
			lstat(tmp, &info);
		put_st_mod(info.st_mode, tmp);
		print_links(info.st_nlink);
		print_user(info.st_uid);
		print_group(info.st_gid);
		print_size(info.st_size);
		print_date(info.st_mtime);
		ft_putstr(file->path);
		write(1, "\n", 1);
		file = file->next;
		free(tmp);
		free(tmp2);
	}
}
