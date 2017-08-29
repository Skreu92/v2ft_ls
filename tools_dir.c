/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:30:39 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/29 12:30:41 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				put_total(int total)
{
	write(1, "total ", 6);
	ft_putnbr(total);
	write(1, "\n", 1);
}

void				ft_error_option(void)
{
	write(1, "ls: illegal option\n", 19);
	write(1, "usage: ls [-lRart] [file ...]\n", 31);
}

void				display_name(t_dir *dir)
{
	write(1, "\n", 1);
	write(1, dir->path, ft_strlen(dir->path));
	write(1, ":\n", 2);
}

void				retrieve_dot_dir(t_file **begin)
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

void				reverse_lst_dir(t_dir **begin)
{
	t_dir *prev;
	t_dir *current;
	t_dir *next;

	prev = NULL;
	current = (*begin);
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	(*begin) = prev;
}
