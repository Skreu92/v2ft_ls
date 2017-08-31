/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:30:23 by Etienne           #+#    #+#             */
/*   Updated: 2017/08/05 17:12:17 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				add_option(char c, t_opt **opt)
{
	if (c == 'l')
		(*opt)->l = 1;
	else if (c == 'a')
		(*opt)->a = 1;
	else if (c == 'R')
		(*opt)->rc = 1;
	else if (c == 'r')
		(*opt)->r = 1;
	else if (c == 't')
		(*opt)->t = 1;
	else
		ft_error_option();
}

