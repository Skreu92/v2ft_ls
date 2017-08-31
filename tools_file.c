/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:13:45 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/29 12:13:48 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_time(t_file **begin)
{
	t_file	*curr;
	t_file	*next;
	char	*tmp;
	time_t	timetmp;

	curr = (*begin);
	while (curr && curr->next != NULL)
	{
		next = curr->next;
		if (next && !(compare(curr, next)))
		{
			tmp = curr->path;
			timetmp = curr->time;
			curr->path = next->path;
			curr->time = next->time;
			next->path = tmp;
			next->time = timetmp;
			curr = (*begin);
		}
		else
			curr = curr->next;
	}
}

void			reverse_lst_file(t_file **begin)
{
	t_file *prev;
	t_file *current;
	t_file *next;

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

void			retrieve_dot_files(t_file **begin)
{
	t_file *curr;

	curr = *begin;
	while (curr->next && curr->path[0] == '.')
		curr = curr->next;
	if (curr->path[0] == '.')
		*begin = NULL;
	else
		*begin = curr;
}

void			sort_path(t_file **begin)
{
	t_file	*curr;
	t_file	*next;
	char	*tmp;

	curr = (*begin);
	while (curr && curr->next != NULL)
	{
		next = curr->next;
		if (next && (ft_strcmp(curr->path, next->path) > 0))
		{
			tmp = curr->path;
			curr->path = next->path;
			next->path = tmp;
			curr = (*begin);
		}
		else
			curr = curr->next;
	}
}
