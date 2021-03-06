/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:57:49 by rbednar           #+#    #+#             */
/*   Updated: 2020/07/22 18:51:05 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "builtins.h"

int			btin_env(t_ltree *pos)
{
	char	**list;
	int		max;

	list = pos->envir;
	max = -1;
	while (list[++max])
		ft_putendl_fd(list[max], STDOUT_FILENO);
	return (0);
}
