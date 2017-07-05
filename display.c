/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:30:23 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/05 01:30:24 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void retrieve_dot_files(t_file **begin)
{
	t_file *lst;
	t_file *tmp;

	lst = *begin;
	while(lst && lst->path[0] == '.')
		lst = lst->next;
	*begin = lst;
	while(lst && lst->next)
	{
		tmp = lst->next;
		if(tmp->path[0] == '.')
			lst->next = tmp->next;
		else
			lst = lst->next;
	}
}

void sort_path(t_file **begin)
{
	t_file *lst;
	t_file *tmp;

	lst = *begin;
	tmp = NULL;
	while(lst && lst->next)
	{
		if(ft_strcmp(lst->path, lst->next->path) > 0 )
		{
			add_lst_file(&tmp, lst->next->path);
			free(lst->next);
			lst->next = NULL;
			break ;
		}
		else
			lst = lst->next;
	}
	lst = *begin;
	*begin = tmp;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_file));
	tmp->next = lst;
}

//void sort_time(t_file **begin)


void display_files(t_file **file ,t_opt *option)
{
	t_file *lst;

	lst = (*file);
	sort_path(&lst);
	if(option->a == 0)
		retrieve_dot_files(&lst);
	if(option->t == 1)
		sort_time(&lst);
	if(option->r == 1)
		reverse_lst(&lst);
	if(option->l == 1)
		displayf_l(&lst);
	else
		displayf(&lst);*/
}
