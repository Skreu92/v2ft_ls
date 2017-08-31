/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:30:23 by Etienne           #+#    #+#             */
/*   Updated: 2017/08/05 17:34:20 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					compare(t_file *curr, t_file *next)
{
	int				diff;

	diff = ft_strcmp(curr->path, next->path);
	if (curr->time > next->time)
		return (1);
	else if (curr->time == next->time && (diff < 0))
		return (1);
	else
		return (0);
}

void				get_time(t_file *file, char *path)
{
	struct stat		info;
	char			*tmp;

	while (file)
	{
		tmp = JOIN(path, file->path);
		if (stat(tmp, &info) == -1)
			lstat(tmp, &info);
		file->time = info.st_mtime;
		file = file->next;
		free(tmp);
	}
}

void				display_files(t_file **file, t_opt *option, char *path)
{
	t_file			*lst;
	char			*tmp;

	lst = (*file);
	if (option->a == 0)
		retrieve_dot_files(&lst);
	if (lst != NULL)
	{
		tmp = ft_strjoin(path, "/");
		get_time(lst, tmp);
		if (option->t == 1)
			sort_time(&lst);
		else
			sort_path(&lst);
		if (option->r == 1)
			reverse_lst_file(&lst);
		free(tmp);
		if (option->l == 0)
			displayf(&lst);
		else
		{
			displayf_l(&lst, path);
		}
	}
}

int					get_width_buf(t_file *lst)
{
	size_t		i;

	i = 0;
	while (lst)
	{
		if (ft_strlen(lst->path) > i)
			i = ft_strlen(lst->path);
		lst = lst->next;
	}
	return ((int)i);
}
