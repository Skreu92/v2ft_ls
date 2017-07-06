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
	t_file *tmp2;

	lst = *begin;
	tmp = NULL;
	while (lst && lst->path[0] == '.')
		lst = lst->next;
	while(lst && lst->next)
	{
		if(ft_strcmp(lst->path, lst->next->path) > 0)
		{
			add_lst_file(&tmp, lst->next->path);
			lst->next = lst->next->next;
			break ;
		}
		else
			lst = lst->next;
	}
	if(!tmp)
		return ;
	lst = *begin;
	while(lst->next && lst->next->path[0] == '.')
		lst = lst->next;
	tmp2 = lst->next;
	lst->next = tmp;
	if(tmp)
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_file));
		tmp->next = tmp2;
	}
}

int compare(char *path1, char *path2)
{
	struct stat buf;
	struct stat buf2;

	stat(path1, &buf);
	stat(path2, &buf2);


	if(buf.st_mtime > buf2.st_mtime)
		return (1);
	else if(buf.st_mtime == buf2.st_mtime && (ft_strcmp(path1, path2) < 0 ))
		return (1);
	else
		return (0);
}
void sort_time(t_file **begin)
{
	t_file *top;
	t_file *curr;
	t_file *prev;
	t_file *largest;

	top = (*begin);
	curr = top;
	largest = top;
	prev = NULL;
    while(curr != NULL) 
    {
        if(prev && (compare(curr->path, prev->path)))
        {
            largest = curr;
        	prev->next = curr->next;
        	largest->next = top;
        	top = largest;
        }
        prev = curr;
        curr = curr->next;
    }
    if(prev == NULL) {
        largest->next = top;
    }
    (*begin) = largest;
}

void reverse_lst(t_file **begin)
{
	t_file *prev;
	t_file *current;
	t_file *next;

	prev = NULL;
	current = (*begin);
	while(current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
	(*begin) = prev;
}


void display_files(t_file **file ,t_opt *option, int total)
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

	if(option->l == 0)
		displayf(&lst);
	else
	{
		if(total)
		{
			write(1, "total ", 6);
			ft_putnbr(total);
			write(1, "\n", 1);
		}
		displayf_l(&lst);
	}
}
