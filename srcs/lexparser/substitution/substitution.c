/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:02:15 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/01 18:55:23 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexparser.h"

/*
** It finds all typs of substitution
** '~'(tilda), $WORD, ${parameter}
*/

int		ft_substitution(t_ltree *sub)
{
	int	err;

	err = 1;
	while (err)
	{
		ft_find_tilda(sub, LINE);
		ft_find_var(sub);
		if ((err = ft_find_curv_var(sub)) & ERR_OUT)
			break ;
		err = 0;
	}
	if (err & ERR_OUT)
	{
		err & ERR_R ? ft_error_redir(sub) : ft_error_vars(sub, 0, NULL);
		ft_lst_ltree_clear(&g_start_list);
	}
	return (err);
}

int		before_add(t_ltree *sub, t_list **list)
{
	int	err;

	sub->token = ft_find_token_sep(&g_cmd[sub->end]);
	ft_local_copy_lines(sub, g_cmd, g_techline.line);
	pre_parsing_cut_glue(sub);
	if (ft_check_null(sub, list) == EXIT)
		return (EXIT);
	if ((err = ft_find_redirection_check(sub)) & ERR_OUT)
	{
		if ((err >> 16 & 0x1FFF) != ERR_TMPFILE)
			ft_error_redir(sub);
		else
			errno(err, err, NULL);
		ft_one_ltree_clear(sub);
		ft_lst_ltree_clear(list);
		return (EXIT);
	}
	return (0);
}

int		ft_check_null(t_ltree *sub, t_list **list)
{
	int i;

	i = sub->start;
	while ((size_t)i <= sub->l_tline.len)
	{
		if (sub->l_tline.line[i] != SPACE)
			break ;
		i++;
	}
	if (i == sub->end && sub->l_tline.line[sub->end] == END_T)
		sub->flags |= ERR_IN;
	else if (i == sub->end)
	{
		sub->flags |= ERR_OUT | ERR_REDIR << 16;
		sub->err_i = i;
		ft_error_redir(sub);
		ft_one_ltree_clear(sub);
		ft_lst_ltree_clear(list);
		return (EXIT);
	}
	return (0);
}

/*
** It gets insert string and insert it to l_cmd and l_tline of sub
** has two types of work - added real techline insert or just TEXT (quoted)
*/

int		insert_str_in_loc_strs(t_ltree *sub, char **insert, int *i, int flag)
{
	char	*buf;
	int		len_ins;

	len_ins = ft_strlen(*insert);
	buf = (char *)ft_xmalloc(sizeof(char) * (sub->l_tline.len + len_ins));
	ft_memcpy(buf, sub->l_cmd, *i);
	ft_memcpy(buf + *i, *insert, len_ins);
	ft_strcpy(buf + *i + len_ins, sub->l_cmd + *i + 1);
	free(sub->l_cmd);
	sub->l_cmd = buf;
	sub->l_tline.alloc_size += len_ins - 1;
	buf = (char *)ft_xmalloc(sizeof(char) * (sub->l_tline.alloc_size));
	ft_memcpy(buf, sub->l_tline.line, *i);
	(sub->l_tline.len += len_ins - 1) > 0 ? sub->end = sub->l_tline.len : 0;
	len_ins += *i;
	(*i)--;
	while (++(*i) < len_ins)
		buf[*i] = (flag == TEXT) ? flag : get_tech_num(*insert[len_ins - *i]);
	ft_memcpy(buf + *i, sub->l_tline.line + *i - ft_strlen(*insert) + 1,
		sub->l_tline.len - *i);
	free(sub->l_tline.line);
	sub->l_tline.line = buf;
	free(*insert);
	(*i)--;
	return (0);
}
