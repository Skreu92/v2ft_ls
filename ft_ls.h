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
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct 		s_opt
{
	int 			a;
	int 			R;
	int				r;
	int 			l;
	int 			t;
}					t_opt;

typedef struct 		s_file
{
	char 			*path;
	struct s_file 	*next;
}					t_file;

typedef struct 		s_dir
{
	char 			*path;
	int 			buflen;
	int 			total;
	struct s_file	*files;
	struct s_dir	*dir;
	struct s_dir	*next;
}					t_dir;

typedef struct 		s_env
{
	t_opt *option;
	t_file *files;
	t_dir *dir;
}					t_env;

void set_opt_dir(t_env *e, int ac, char **av);
void display_files(t_file **lst,t_opt *option);
void add_lst_file(t_file **file, char *path);
#endif
