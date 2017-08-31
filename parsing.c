/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 00:30:44 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/05 00:30:46 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*create_file(char *path)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->path = ft_strdup(path);
	file->next = NULL;
	return (file);
}

t_dir		*create_dir(char *path)
{
	t_dir *dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->path = ft_strdup(path);
	dir->total = 0;
	dir->files = NULL;
	dir->dir = NULL;
	dir->next = NULL;
	return (dir);
}

void					add_lst_dir(t_dir **dir, char *path)
{
	t_dir *lst;

	if (!(*dir))
	{
		(*dir) = create_dir(path);
	}
	else
	{
		lst = *dir;
		while (lst->next)
			lst = lst->next;
		lst->next = create_dir(path);
	}
}

void					add_lst_file(t_file **file, char *path)
{
	t_file *lst;

	if (!(*file))
	{
		(*file) = create_file(path);
	}
	else
	{
		lst = *file;
		while (lst && lst->next)
			lst = lst->next;
		lst->next = create_file(path);
	}
}

void					add_file_dir(char *path, t_env *e)
{
	DIR *dir;
	int	fd;

	if ((dir = opendir(path)) != NULL)
	{
		add_lst_dir(&e->dir, path);
		closedir(dir);
		return ;
	}
	else if ((fd = open(path, O_RDONLY)) > 0)
	{
		add_lst_file(&e->files, path);
		close(fd);
		return ;
	}
	else
	{
		write(1, "ls: ", 4);
		write(1, path, ft_strlen(path));
		write(1, "No such file or directory\n", 26);
	}
}

void					set_opt_dir(t_env *e, int ac, char **av)
{
	int i;
	int j;

	i = 1;
	e->files = NULL;
	e->dir = NULL;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && !e->files && !e->dir)
			while (av[i][++j])
				add_option(av[i][j], &e->option);
		else
			add_file_dir(av[i], e);
		i++;
	}
	if (e->files == NULL && e->dir == NULL)
		add_file_dir(".", e);
}
