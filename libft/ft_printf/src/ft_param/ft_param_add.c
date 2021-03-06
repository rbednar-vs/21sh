/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcraydle <fcraydle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:42:07 by fcraydle          #+#    #+#             */
/*   Updated: 2019/09/20 17:42:07 by fcraydle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static void		ft_get_length(char **str, t_param *new)
{
	if (**str == 'L' || **str == 'l' || **str == 'h' ||
											**str == 'j' || **str == 'z')
	{
		new->length += **str;
		*str += 1;
	}
	if ((new->length == 'l' && **str == 'l') ||
		(new->length == 'h' && **str == 'h'))
	{
		new->length += **str;
		*str += 1;
	}
}

static void		ft_flags(t_param *new, char **str)
{
	while (**str && (**str == '0' || **str == '+' || **str == '-' ||
			**str == ' ' || **str == '#'))
	{
		(**str == '#') ? new->hasht = 1 : 0;
		(**str == '0') ? new->zero = 1 : 0;
		(**str == '-') ? new->minus = 1 : 0;
		(**str == '+') ? new->plus = 1 : 0;
		(**str == ' ') ? new->space = 1 : 0;
		*str += 1;
	}
	(new->space == 1 && new->plus == 1) ? new->space = 0 : 1;
	(new->zero == 1 && new->minus == 1) ? new->zero = 0 : 1;
}

static void		ft_get_width(t_param *new, char **str, va_list ap)
{
	if (**str == '*')
	{
		new->width = va_arg(ap, int);
		if (new->width < 0)
		{
			new->width *= -1;
			new->minus = 1;
		}
		*str = *str + 1;
	}
	else
	{
		new->width = ft_atoi_pf(*str);
		while (**str && **str >= '0' && **str <= '9')
			*str += 1;
	}
}

static int		ft_prec(t_param *new, char **str, va_list ap)
{
	if (*(*str + 1) >= '0' && *(*str + 1) <= '9')
		new->precision = ft_atoi_pf(*str + 1);
	else if (*(*str + 1) == '-')
		new->precision = -2;
	else if (*(*str + 1) == '*')
	{
		new->precision = va_arg(ap, int);
		*str = *str + 1;
	}
	else if (*(*str + 1) == '\0')
		return (-1);
	else
		new->precision = 0;
	*str += 1;
	while (**str && **str >= '0' && **str <= '9')
		*str += 1;
	return (1);
}

int				ft_param_add(t_param *new, char **str, va_list ap)
{
	ft_flags(new, str);
	ft_get_width(new, str, ap);
	if (**str == '*' || (**str >= '0' && **str <= '9'))
		ft_get_width(new, str, ap);
	if (**str == '.')
	{
		if ((ft_prec(new, str, ap)) == -1)
			return (-1);
	}
	ft_get_length(str, new);
	if (**str && (**str == '0' || **str == '+' || **str == '-' ||
			**str == ' ' || **str == '#'))
		ft_flags(new, str);
	return (1);
}
