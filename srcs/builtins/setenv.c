/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:04 by rbednar           #+#    #+#             */
/*   Updated: 2020/07/22 18:51:05 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "builtins.h"

/*
** bash: export: `   fu=ft': not a valid identifier
** erroring for not valig args
*/

int			btin_setenv(t_ltree *pos)
{
	int	i;
	int	len;

	i = 1;
	while (i <= pos->ar_c)
	{
		pos->err_i = i;
		len = ft_strlen(pos->ar_v[pos->err_i]);
		assignment(pos, len);
		i++;
	}
	return (0);
}