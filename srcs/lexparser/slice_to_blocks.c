/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_to_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:09:27 by rbednar           #+#    #+#             */
/*   Updated: 2020/07/27 11:00:49 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexparser.h"

/*
** Function add commands whith args and fd to list
*/

int		ft_block_add_to_list(t_ltree *block, t_list **list)
{
	t_ltree	*final;

	final = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	while (ft_check_andor_pipes(block, final, list))
	{
		if (final->flags & ERR_OUT)
		{
			ft_one_ltree_clear(final);
			ft_lst_ltree_clear(list);
			return (EXIT);
		}
		block->flags &= ~GR_START;
		block->start = final->end + 1;
		if (before_add(final, list) == EXIT)
			return (EXIT);
		ft_add_list_to_end(list, ft_lstnew(final, sizeof(t_ltree)));
		if (final->flags & LOG_AND_OUT || final->flags & LOG_OR_OUT)
			block->start += 1;
		ltree_init(final);
	}
	free(final);
	return (0);
}

/*
** Function forwards list commands until GR_START
*/

int		ft_block_foward(t_ltree **sub, t_list **start)
{
	while (*start)
	{
		if ((*start = (*start)->next))
			*sub = (t_ltree *)((*start)->content);
		else
			break ;
		if ((*sub)->flags & GR_START)
			break ;
	}
	return (0);
}

/*
** Function start list commands
*/

int		ft_block_start(t_list **list)
{
	t_ltree	*sub;
	t_list	*start;
	int		out_flag;

	start = *list;
	out_flag = 0;
	while (start)
	{
		sub = (t_ltree *)(start->content);
		if (before_exec(sub) == EXIT)
			break ;
		if (!(sub->flags & ERR_IN))
		{
			if ((out_flag != 0 && (sub->flags & LOG_AND_IN)) ||
				(out_flag == 0 && (sub->flags & LOG_OR_IN)))
			{
				start = start->next;
				continue ;
			}
			out_flag = exec_core(sub, 0);
		}
		start = start->next;
	}
	ft_lst_ltree_clear(list);
	return (0);
}

/*
** Fucntion slice command string to blocks and send add it to start list
*/

int		ft_slice(void)
{
	t_ltree		block;
	size_t		i;

	i = -1;
	ltree_init(&block);
	if (g_prompt.prompt_func != heredoc_prompt)
	{
		g_heredoc.list = NULL;
		g_start_list = NULL;
		while (++i <= g_techline.len)
		{
			block.flags = GR_START;
			if (g_techline.line[i] == SCOLON || g_cmd[i] == '\0')
			{
				block.end = i;
				if (ft_block_add_to_list(&block, &g_start_list) == EXIT)
					return (EXIT);
				block.start = i + 1;
			}
		}
	}
	return (ft_check_is_heredoc(0));
}
