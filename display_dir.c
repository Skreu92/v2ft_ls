/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 10:19:13 by Etienne           #+#    #+#             */
/*   Updated: 2017/08/05 17:26:41 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			get_all_files(t_dir **lst, int a)
{
	DIR				*dirp;
	t_dir			*direc;
	struct dirent	*dir;
	char			*tmp;
	char			*tmp2;
	struct stat		info;

	direc = (*lst);
	dirp = opendir(direc->path);
	if (!dirp)
		return ;
	while ((dir = readdir(dirp)) != NULL)
	{
		tmp2 = ft_strjoin(direc->path, "/");
		tmp = ft_strjoin(tmp2, dir->d_name);
		free(tmp2);
		stat(tmp, &info);
		direc->total += info.st_blocks;
		add_lst_file(&direc->files, dir->d_name);
		free(tmp);
		if (dir->d_type == DT_DIR && ft_strcmp("..", dir->d_name) &&
			ft_strcmp(".", dir->d_name))
		{
			tmp2 = ft_strjoin(direc->path, "/");
			tmp = ft_strjoin(tmp2, dir->d_name);
			free(tmp2);
			if (a == 0 && !(dir->d_name[0] == '.'))
				add_lst_dir(&direc->dir, tmp);
			if (a == 1)
				add_lst_dir(&direc->dir, tmp);
			free(tmp);
		}
	}
	(void)closedir(dirp);
}

void			display_name(t_dir *dir)
{
	write(1, "\n", 1);
	write(1, dir->path, ft_strlen(dir->path));
	write(1, ":\n", 2);
}

int				get_width_buf(t_file *lst)
{
	size_t i;

	i = 0;
	while (lst)
	{
		if (ft_strlen(lst->path) > i)
			i = ft_strlen(lst->path);
		lst = lst->next;
	}
	return ((int)i);
}

void			display_width(char *str, int width, int *i)
{
	struct winsize	max;

	ioctl(0, TIOCGWINSZ, &max);
	if (*i + width > max.ws_col)
	{
		write(1, "\n", 2);
		*i = 0;
	}
	write(1, str, width);
}

void			displayf(t_file **file)
{
	t_file		*lst;
	int			width;
	char		*tmp;
	int			i;

	lst = (*file);
	width = get_width_buf(lst) + 1;
	i = 0;
	while (lst)
	{
		tmp = malloc(sizeof(char) * (width + 1));
		ft_memset(tmp, ' ', width);
		ft_strncpy(tmp, lst->path, ft_strlen(lst->path));
		display_width(tmp, width, &i);
		i += width;
		lst = lst->next;
		free(tmp);
	}
	write(1, "\n", 1);
}

void			retrieve_dot_dir(t_file **begin)
{
	t_file *lst;
	t_file *tmp;

	lst = *begin;
	while (lst && lst->path[0] == '.')
		lst = lst->next;
	*begin = lst;
	while (lst && lst->next)
	{
		tmp = lst->next;
		if (tmp->path[0] == '.')
			lst->next = tmp->next;
		else
			lst = lst->next;
	}
}

void			release_lst_file(t_file *lst)
{
	t_file *tmp;

	while (lst)
	{
		tmp = lst->next;
		file_free(lst);
		lst = tmp;
	}
}

void			put_total(int total)
{
	write(1, "total ", 6);
	ft_putnbr(total);
	write(1, "\n", 1);
}

void			display_dir(t_dir **dir, t_opt *option)
{
	t_dir *lst;
	t_dir *tmp;

	lst = (*dir);
	if (lst)
	{
		get_all_files(&lst, option->a);
		if (option->l)
			put_total(lst->total);
		if (option->r)
		{
			reverse_lst_file(&lst->files);
			reverse_lst_dir(&lst->dir);
		}
		display_files(&lst->files, option, lst->path);
		release_lst_file(lst->files);
		if (option->R == 1 && lst->dir != NULL)
			while (lst->dir)
			{
				tmp = lst->dir;
				display_name(lst->dir);
				display_dir(&lst->dir, option);
				lst->dir = lst->dir->next;
				dir_free(tmp);
			}
	}
}
