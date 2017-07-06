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
	e->option = malloc(sizeof(t_opt));
	e->option->a = 0;
	e->option->R = 0;
	e->option->r = 0;
	e->option->l = 0;
	e->option->t = 0;
}


int main(int ac, char **av)
{
	t_env *e;

	e = malloc(sizeof(t_env));
	init_env(e);
	set_opt_dir(e, ac, av);
	if(e->files)
		display_files(&e->files, e->option, 0);
	if(e->dir)
		display_dir(&e->dir, e->option);

}