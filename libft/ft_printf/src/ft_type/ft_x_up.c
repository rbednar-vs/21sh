/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaggon <ehaggon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:48:50 by fcraydle          #+#    #+#             */
/*   Updated: 2019/10/15 20:52:28 by ehaggon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static void	minus_neg(t_param list, char *i, int tmp, t_buf *buf)
{
	if ((list.width - (list.precision > tmp ? list.precision : tmp) -
											list.hasht) >= 0 && list.zero != 1)
		ft_buf_add_s(buf, ft_memnew_pf(list.width - (list.precision > tmp ?
			list.precision : tmp) - list.hasht, ' '), 0);
	if (list.hasht != 0)
		ft_buf_add_s(buf, "0X", 1);
	if ((list.width - (list.precision > tmp ? list.precision : tmp) -
											list.hasht) >= 0 && list.zero == 1)
		ft_buf_add_s(buf, ft_memnew_pf(list.width - tmp -
			list.hasht, '0'), 0);
	if (list.precision > tmp)
		ft_buf_add_s(buf, ft_memnew_pf(list.precision - tmp, '0'), 0);
	ft_buf_add_s(buf, i, 0);
}

static void	minus_pos(t_param list, char *i, int tmp, t_buf *buf)
{
	if (list.hasht != 0)
		ft_buf_add_s(buf, "0X", 1);
	if (list.precision > tmp)
		ft_buf_add_s(buf, ft_memnew_pf(list.precision - tmp, '0'), 0);
	ft_buf_add_s(buf, i, 0);
	if ((list.width - (list.precision > tmp ? list.precision : tmp) -
											list.hasht) >= 0 && list.zero != 1)
		ft_buf_add_s(buf, ft_memnew_pf(list.width - (list.precision > tmp ?
			list.precision : tmp) - list.hasht, ' '), 0);
}

static void	str_up(char *i)
{
	int	j;

	j = 0;
	while (i[j] != 0)
	{
		if (i[j] >= 'a' && i[j] <= 'z')
			i[j] = i[j] - 32;
		j++;
	}
}

static void	ft_type_x(t_param list, char *i, t_buf *buf)
{
	int		tmp;

	str_up(i);
	tmp = ft_strlen_pf(i);
	list.precision > -1 ? list.zero = 0 : 0;
	if (*i != '0')
	{
		list.hasht == 1 ? list.hasht = 2 : 0;
		if (list.minus == 0)
			minus_neg(list, i, tmp, buf);
		else
			minus_pos(list, i, tmp, buf);
	}
	else
	{
		tmp = 0;
		list.precision == -1 ? list.hasht = 1 : 0;
		if (list.minus == 0)
			ft_minus_neg_null(list, tmp, buf);
		else
			ft_minus_pos_null(list, tmp, buf);
	}
}

void		ft_x_up(t_param list, va_list ap, t_buf *buf)
{
	if (list.length == 0)
		ft_type_x(list,
			ft_itoa_base_ll(va_arg(ap, unsigned), 16), buf);
	else if (list.length == 'l')
		ft_type_x(list,
			ft_itoa_base_ll(va_arg(ap, unsigned long), 16), buf);
	else if (list.length == 'l' + 'l')
		ft_type_x(list,
		ft_itoa_base_ll(va_arg(ap, unsigned long long),
			16), buf);
	else if (list.length == 'h')
		ft_type_x(list,
				ft_itoa_base_ll((unsigned short)va_arg(ap, int), 16), buf);
	else if (list.length == 'h' + 'h')
		ft_type_x(list,
				ft_itoa_base_ll((unsigned char)va_arg(ap, int), 16), buf);
	else if (list.length == 'j')
		ft_type_x(list,
				ft_itoa_base_ll((uintmax_t)va_arg(ap, uintmax_t), 16), buf);
	else if (list.length == 'z')
		ft_type_x(list,
				ft_itoa_base_ll((size_t)va_arg(ap, size_t), 16), buf);
}
