/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 10:19:13 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/05 10:19:14 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void get_all_files(t_dir **lst)
{
	DIR *dirp;
	t_dir *direc;
	struct dirent *dir;
	char *tmp;
	struct stat info;

	direc = (*lst);
	dirp = opendir(direc->path);
	while((dir = readdir(dirp)) != NULL)
	{
		stat(dir->d_name, &info);
		direc->total += info.st_blocks;	
		add_lst_file(&direc->files, dir->d_name);
		if(dir->d_type == DT_DIR && ft_strcmp("..", dir->d_name) && ft_strcmp(".", dir->d_name))
		{
					tmp = malloc(sizeof(char) * (ft_strlen(direc->path) + dir->d_namlen + 2));
					tmp = ft_strjoin(ft_strjoin(direc->path, "/"), dir->d_name);
					add_lst_dir(&direc->dir, tmp);
					free(tmp);
				}
	}
	closedir(dirp);
}

void display_name(t_dir *dir)
{
	static int i;

	i = 0;
	if(i > 0 )
	{
		write(1, "\n", 1);
		write(1, dir->path, ft_strlen(dir->path));
		write(1, ":\n", 2);
	}
	i++;
}

int	get_width_buf(t_file *lst)
{
	size_t i;

	i = 0;

	while(lst)
	{
		if(ft_strlen(lst->path) > i)
			i = ft_strlen(lst->path);
		lst =lst->next;
	}
	return ((int)i);
}

void display_width(char *str, int i)
{
	struct winsize max;
	static int count = 0;

    ioctl(0, TIOCGWINSZ , &max);
	if(count + i > max.ws_col)
	{
		write(1, "\n", 1);
		count = 0;
	}
	write(1, str, i);
	count += i;
}

void displayf(t_file **file)
{
	t_file *lst;
	int i;
	char *tmp;

	lst = (*file);
	i = get_width_buf(lst) + 1;
	while (lst)
	{
		tmp = malloc(sizeof(char) * (i));
		ft_memset(tmp, ' ', i);
		ft_strncpy(tmp, lst->path, ft_strlen(lst->path));
		display_width(tmp, i);
		lst = lst->next;
		free(tmp);
	}
	write(1, "\n", 1);
}

void display_dir(t_dir **dir,t_opt *option)
{
	t_dir *lst;

	lst = (*dir);
	while(lst)
	{
		display_name(lst);
		get_all_files(&lst);
		display_files(&lst->files, option, lst->total);
		if(option->R == 1 && lst->dir != NULL)
		{
			display_dir(&lst->dir, option);
		}
		lst = lst->next;
	}

}
