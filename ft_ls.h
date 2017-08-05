/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 23:54:41 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/04 23:54:45 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <stdio.h>
# include <ctype.h>
# include <sys/dir.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

typedef struct		s_opt
{
	int				a;
	int				R;
	int				r;
	int				l;
	int				t;
}					t_opt;

typedef struct		s_file
{
	char			*path;
	struct s_file	*next;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	int				buflen;
	int				total;
	struct s_file	*files;
	struct s_dir	*dir;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_env
{
	t_opt			*option;
	t_file			*files;
	t_dir			*dir;
}					t_env;

void				set_opt_dir(t_env *e, int ac, char **av);
void				displayf(t_file **file);
void				display_dir(t_dir **dir, t_opt *option);
void				display_files(t_file **lst, t_opt *option, char *path);
void				displayf_l(t_file **file, char *path);
void				display_name(t_dir *dir);

void				add_lst_file(t_file **file, char *path);
void				add_lst_dir(t_dir **dir, char *path);

void				retrieve_dot_files(t_file **begin);
void				sort_path(t_file **begin);
void				reverse_lst_file(t_file **begin);
void				reverse_lst_dir(t_dir **begin);
void				file_free(t_file *file);
void				dir_free(t_dir *dir);
void				release_lst_dir(t_dir *lst);

#endif
