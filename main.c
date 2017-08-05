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

static void			init_env(t_env *e)
{
	e->option->a = 0;
	e->option->R = 0;
	e->option->r = 0;
	e->option->l = 0;
	e->option->t = 0;
}

void				file_free(t_file *file)
{
	free(file->path);
	free(file);
}

void				dir_free(t_dir *dir)
{
	free(dir->path);
	free(dir);
}

int					main(int ac, char **av)
{
	t_env *e;
	t_dir *tmp;

	e = (t_env *)malloc(sizeof(t_env));
	e->option = (t_opt *)malloc(sizeof(t_opt));
	init_env(e);
	set_opt_dir(e, ac, av);
	if (e->files)
		display_files(&e->files, e->option, ".");
	if (e->files && e->dir)
		write(1, "\n", 1);
	while (e->dir)
	{
		if (ft_strcmp(e->dir->path, ".") != 0)
		{
			write(1, e->dir->path, ft_strlen(e->dir->path));
			write(1, ":\n", 2);
		}
		display_dir(&e->dir, e->option);
		tmp = e->dir;
		e->dir = e->dir->next;
	}
	return (0);
}
