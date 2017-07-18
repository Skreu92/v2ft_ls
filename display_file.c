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
	t_file *curr;
	t_file *next;

	curr = *begin;
	while(curr && curr->next)
	{
		next = curr->next;
		if(next->path[0] == '.')
		{
			curr->next = next->next;
			free(next->path);
			free(next);
		}
		else
			curr = curr->next;
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
			tmp2 = lst->next->next;
			free(lst->next);
			lst->next = tmp2;
			break ;
		}
		else
			lst = lst->next;
	}
	lst = *begin;
	tmp2 = NULL;
	while(lst && lst->path[0] == '.')
	{
		add_lst_file(&tmp2, lst->path);
		lst = lst->next;
	}
	while(tmp)
	{
		add_lst_file(&tmp2, tmp->path);
		tmp = tmp->next;
	}
	while(lst)
	{
		add_lst_file(&tmp2, lst->path);
		lst = lst->next;
	}
	(*begin) = tmp2;
}

int compare(char *path1, char *path2)
{
	struct stat buf;
	struct stat buf2;

	stat(path1, &buf);
	stat(path2, &buf2);
	free(path1);
	free(path2);
	if(buf.st_mtime > buf2.st_mtime)
		return (1);
	else if(buf.st_mtime == buf2.st_mtime && (ft_strcmp(path1, path2) < 0 ))
		return (1);
	else
		return (0);
}

void sort_time(t_file **begin, char *path)
{
	t_file *curr;
	t_file *next;
	char *tmp;
	char *tmp2;
	curr = (*begin);
    while(curr && curr->next != NULL) 
    {
    	next = curr->next;
    	tmp = ft_strjoin(path, curr->path);
    	tmp2 = ft_strjoin(path, next->path);
        if(next->next && (!compare(tmp,tmp2)))
        {
            tmp = curr->path;
            curr->path = next->path;
   			next->path = tmp;
   			curr = (*begin);
        }
        else
        	curr = curr->next;
    }
    free(tmp);
    free(tmp2);
}

void reverse_lst_file(t_file **begin)
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

void reverse_lst_dir(t_dir **begin)
{
	t_dir *prev;
	t_dir *current;
	t_dir *next;

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


void display_files(t_file **file ,t_opt *option, char *path)
{
	t_file *lst;
	char *tmp;

	lst = (*file);
	tmp = ft_strjoin(path, "/");
	//sort_path(&lst);
	if(option->a == 0)
		retrieve_dot_files(&lst);
	if(option->r == 1)
		reverse_lst_file(&lst);
	if(option->t == 1)
		sort_time(&lst, tmp);
	free(tmp);
	if(option->l == 0)
		displayf(&lst);
	else
	{
		displayf_l(&lst, path);
	}
}
