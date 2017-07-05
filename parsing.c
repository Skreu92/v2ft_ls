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

static void ft_error_option()
{
	write(1, "ls: illegal option\n", 19);
	write(1, "usage: ls [-lRart] [file ...]\n", 31);;
}

static void add_option(char c, t_opt **opt)
{
	if(c == 'l' && (*opt)->l == 0)
		(*opt)->l = 1;
	else if (c == 'a' && (*opt)->a == 0)
		(*opt)->a = 1;
	else if (c == 'R' && (*opt)->R == 0)
		(*opt)->R = 1;
	else if (c == 'r' && (*opt)->r == 0)
		(*opt)->r = 1;
	else if (c == 't' && (*opt)->t == 0)
		(*opt)->t = 1;
	else 
		ft_error_option();

}

void add_lst_dir(t_dir **dir, char *path)
{
	t_dir *lst;
	char *tmp;

	if(!(*dir))
	{
		(*dir) = malloc(sizeof(t_dir));
		tmp = malloc(sizeof(char) * (ft_strlen(path) + 1));
		(*dir)->path = ft_strcpy(tmp, path);
		(*dir)->files = NULL;
		(*dir)->dir = NULL;
		(*dir)->next = NULL;
	}
	else
	{
		lst = *dir;
		while(lst->next)
			lst = lst->next;
		lst->next = malloc(sizeof(t_dir));
		tmp = malloc(sizeof(char) * (ft_strlen(path) + 1));
		lst->next->path = ft_strcpy(tmp, path);
		lst->next->files = NULL;
		lst->next->dir = NULL;
		lst->next->next = NULL;
	}
}

void add_lst_file(t_file **file, char *path)
{
	t_file *lst;
	char *tmp;

	if(!(*file))
	{
		(*file) = malloc(sizeof(t_file));
		tmp = malloc(sizeof(char) * (ft_strlen(path) + 1));
		(*file)->path = ft_strcpy(tmp, path);
		(*file)->next = NULL;
	}
	else
	{
		lst = *file;
		while(lst->next)
			lst = lst->next;
		lst->next = malloc(sizeof(t_file));
		tmp = malloc(sizeof(char) * (ft_strlen(path)+1));
		lst->next->path = ft_strcpy(tmp, path);
		lst->next->next = NULL;
	}
}


void add_file_dir(char *path, t_env *e)
{
	DIR *dir;
	int fd;

	if((dir = opendir(path)) != NULL)
	{
		add_lst_dir(&e->dir, path);
		closedir(dir);
		return ;
	}
	else if((fd = open(path, O_RDONLY)) > 0)
	{
		add_lst_file(&e->files, path);
		close(fd);
		return ;
	}
	else
	{
		write(1, "ls: ", 4);
		write(1 , path, ft_strlen(path));
		write(1, " No such file or directory\n", 27);
	}
}

void set_opt_dir(t_env *e, int ac, char **av)
{
	int i;
	int j;

	i = 1;
	e->files = NULL;
	e->dir = NULL;
	while (i < ac)
	{
		
		if(av[i][0] == '-' && !e->files && !e->dir)
		{
			j = 0;
			while(av[i][++j])
				add_option(av[i][j], &e->option);
		}
		else
			add_file_dir(av[i], e);
		i++;
	}
	if(e->files == NULL && e->dir == NULL)
		add_file_dir(".", e);
}
