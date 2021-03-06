/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:19:07 by rbednar           #+#    #+#             */
/*   Updated: 2020/07/25 15:31:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "help_lib.h"

static char		*ft_find_token_sep_one(char *str)
{
	if (ft_strlen(str) > 0)
	{
		if (!ft_strncmp(str, ";", 1))
			return (ft_strndup(";", 1));
		if (!ft_strncmp(str, "&", 1))
			return (ft_strndup("&", 1));
		if (!ft_strncmp(str, ";", 1))
			return (ft_strndup(";", 1));
		if (!ft_strncmp(str, "|", 1))
			return (ft_strndup("|", 1));
		if (!ft_strncmp(str, "(", 1))
			return (ft_strndup("(", 1));
		if (!ft_strncmp(str, ")", 1))
			return (ft_strndup(")", 1));
		if (!ft_strncmp(str, ">", 1))
			return (ft_strndup(">", 1));
		if (!ft_strncmp(str, "<", 1))
			return (ft_strndup("<", 1));
	}
	return (NULL);
}

char			*ft_find_token_sep(char *str)
{
	if (ft_strlen(str) > 1)
	{
		if (!ft_strncmp(str, "&&", 2))
			return (ft_strndup("&&", 2));
		else if (!ft_strncmp(str, "||", 2))
			return (ft_strndup("||", 2));
		else if (!ft_strncmp(str, ";;", 2))
			return (ft_strndup(";;", 2));
		else if (!ft_strncmp(str, "<<", 2))
			return (ft_strndup("<<", 2));
		else if (!ft_strncmp(str, ">>", 2))
			return (ft_strndup(">>", 2));
		else if (!ft_strncmp(str, "<&", 2))
			return (ft_strndup("<&", 2));
		else if (!ft_strncmp(str, ">&", 2))
			return (ft_strndup(">&", 2));
		else if (ft_strlen(str) > 2)
			if (!ft_strncmp(str, "<<-", 3))
				return (ft_strndup("<<-", 3));
	}
	return (ft_find_token_sep_one(str));
}
