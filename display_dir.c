/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 10:19:13 by Etienne           #+#    #+#             */
/*   Updated: 2017/08/05 17:26:41 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			check_add(char *name, t_dir *dir, int a)
{
	char			*tmp;
	char			*tmp2;

	tmp2 = ft_strjoin(dir->path, "/");
	tmp = ft_strjoin(tmp2, name);
	free(tmp2);
	if (a == 0 && !(name[0] == '.'))
		add_lst_dir(&dir->dir, tmp);
	if (a == 1)
		add_lst_dir(&dir->dir, tmp);
	free(tmp);
}

void			get_all_files(t_dir **lst, int a)
{
	DIR				*dirp;
	struct dirent	*dir;
	char			*tmp;
	char			*tmp2;
	struct stat		info;

	dirp = opendir((*lst)->path);
	if (!dirp)
		return ;
	while ((dir = readdir(dirp)) != NULL)
	{
		tmp2 = ft_strjoin((*lst)->path, "/");
		tmp = ft_strjoin(tmp2, dir->d_name);
		free(tmp2);
		stat(tmp, &info);
		(*lst)->total += info.st_blocks;
		add_lst_file(&(*lst)->files, dir->d_name);
		free(tmp);
		if (dir->d_type == DT_DIR && ft_strcmp("..", dir->d_name) &&
			ft_strcmp(".", dir->d_name))
			check_add(dir->d_name, (*lst), a);
	}
	(void)closedir(dirp);
}

void			display_width(char *str, int width, int *i)
{
	struct winsize	max;

	ioctl(0, TIOCGWINSZ, &max);
	if (*i + width > max.ws_col)
	{
		write(1, "\n", 2);
		*i = 0;
	}
	write(1, str, width);
}

void			displayf(t_file **file)
{
	t_file		*lst;
	int			width;
	char		*tmp;
	int			i;

	lst = (*file);
	width = get_width_buf(lst) + 1;
	i = 0;
	while (lst)
	{
		tmp = malloc(sizeof(char) * (width + 1));
		ft_memset(tmp, ' ', width);
		ft_strncpy(tmp, lst->path, ft_strlen(lst->path));
		display_width(tmp, width, &i);
		i += width;
		lst = lst->next;
		free(tmp);
	}
	write(1, "\n", 1);
}

void			display_dir(t_dir **dir, t_opt *option)
{
	t_dir *lst;
	t_dir *tmp;

	lst = (*dir);
	if (lst)
	{
		get_all_files(&lst, option->a);
		if (option->l)
			put_total(lst->total);
		if (option->r)
			reverse_lst_dir(&lst->dir);
		display_files(&lst->files, option, lst->path);
		release_lst_file(lst->files);
		if (option->rc == 1 && lst->dir != NULL)
			while (lst->dir)
			{
				tmp = lst->dir;
				display_name(lst->dir);
				display_dir(&lst->dir, option);
				lst->dir = lst->dir->next;
				dir_free(tmp);
			}
	}
}
