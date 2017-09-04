/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 14:12:06 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/29 14:12:07 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_acl(mode_t mode, char *path)
{
	ssize_t		buflen;
	acl_t		a;

	buflen = (S_ISLNK(mode)) ? (listxattr(path, (char*)NULL, 0, XATTR_NOFOLLOW))
	: (listxattr(path, (char*)NULL, 0, 0));
	a = (S_ISLNK(mode)) ? (acl_get_link_np(path, ACL_TYPE_EXTENDED))
	: (acl_get_file(path, ACL_TYPE_EXTENDED));
	if (buflen > 0)
		ft_putchar('@');
	else if (a != NULL)
		ft_putchar('+');
	else
		ft_putchar(' ');
}

int check_is_link(char *file, char *direc)
{
	DIR				*dirp;
	struct dirent	*dir;
	struct stat		tmp;

	dirp = opendir(direc);
	while ((dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dir->d_name, file) == 0)
		{
			if (dir->d_type == DT_LNK &&
				(lstat(JOIN(JOIN(direc, "/"), file), &tmp) == 0))
			{
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);

}
void			put_st_mod(mode_t mode, char *path, char *dir)
{
	if (S_ISDIR(mode))
		ft_putchar('d');
	else if (check_is_link(path, dir))
		ft_putchar('l');
	else if (S_ISREG(mode))
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
}

void			print_links(nlink_t link)
{
	ft_putchar(' ');
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
}
