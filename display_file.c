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

int				compare(char *path1, char *path2)
{
	struct stat		buf;
	struct stat		buf2;
	int				diff;

	stat(path1, &buf);
	stat(path2, &buf2);
	if (stat(path1, &buf) == -1)
		lstat(path1, &buf);
	if (stat(path2, &buf2) == -1)
		lstat(path2, &buf2);
	diff = ft_strcmp(path1, path2);
	free(path1);
	free(path2);
	if (buf.st_mtime > buf2.st_mtime)
		return (1);
	else if (buf.st_mtime == buf2.st_mtime && (diff < 0))
		return (1);
	else
		return (0);
}

void			display_files(t_file **file, t_opt *option, char *path)
{
	t_file	*lst;
	char	*tmp;

	lst = (*file);
	if (option->a == 0)
		retrieve_dot_files(&lst);
	if (lst != NULL)
	{
		tmp = ft_strjoin(path, "/");
		sort_path(&lst);
		if (option->t == 1)
			sort_time(&lst, tmp);
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

int				get_width_buf(t_file *lst)
{
	size_t i;

	i = 0;
	while (lst)
	{
		if (ft_strlen(lst->path) > i)
			i = ft_strlen(lst->path);
		lst = lst->next;
	}
	return ((int)i);
}
