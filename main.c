/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 23:55:22 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/04 23:55:24 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void init_env(t_env *e)
{
	e->option->a = 0;
	e->option->R = 0;
	e->option->r = 0;
	e->option->l = 0;
	e->option->t = 0;
}

void file_free(t_file *file)
{
	free(file->path);
	free(file);
}
void dir_free(t_dir *dir)
{
	free(dir->path);
	if(dir->files)
		file_free(dir->files);
	if(dir->dir)
		dir_free(dir->dir);
	free(dir);
}
void release_env(t_env *e)
{
	t_file *tmp_file;
	t_dir *tmp_dir;

	while(e->files)
	{
		tmp_file = e->files;
		e->files = e->files->next;
		file_free(tmp_file);
	}
	while(e->dir)
	{
		tmp_dir = e->dir;
		e->dir = e->dir->next;
		dir_free(tmp_dir);
	}
	free(e->option);
}

int main(int ac, char **av)
{
	t_env *e;
	t_dir *tmp;

	e = (t_env *)malloc(sizeof(t_env));
	e->option = (t_opt *)malloc(sizeof(t_opt));
	init_env(e);
	set_opt_dir(e, ac, av);
	if(e->files)
		display_files(&e->files, e->option, ".");
	if(e->files && e->dir)
		write(1, "\n", 1);
	while(e->dir)
	{
		if(ft_strcmp(e->dir->path, ".") != 0 && !e->dir->next)
		{
			write(1, e->dir->path, ft_strlen(e->dir->path));
			write(1, ":\n", 2);
		}
		display_dir(&e->dir, e->option);
		tmp = e->dir;
		e->dir = e->dir->next;
	}
	free(e->option);
	free(e);

}