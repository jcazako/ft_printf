/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_space_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 20:03:08 by jcazako           #+#    #+#             */
/*   Updated: 2016/03/21 22:00:03 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_signe_moins(t_opt opt)
{
	if (ft_check_charset(opt.type, "di"))
	{
		if ((!opt.m_len && (int)opt.conv < 0)
			|| (opt.m_len == 'h' && (short)opt.conv < 0)
			|| (opt.m_len == 'H' && (char)opt.conv < 0)
			|| (ft_check_charset(opt.m_len, "lL") && opt.conv < 0))
		return (-1);
	}
	else if (opt.type == 'D' && opt.conv < 0)
		return (-1);
	return (1);
}

static int	print_plus(t_opt opt, int *ret)
{
	if (opt.attri.plus && ft_check_charset(opt.type, "diD"))
	{
		(*ret)++;
		return (1);
	}
	return (0);
}

static int      print_moins(t_opt opt, int *ret)
{
	if (check_signe_moins(opt) == -1)
	{
			(*ret)++;
		return (1);
	}
	return (0);
}

static int	print_opt_space(t_opt opt, int *ret)
{
	if (opt.attri.space && !*ret)
	{
		if (ft_check_charset(opt.type, "di"))
		{
			if ((int)opt.conv > 0 && !opt.attri.plus)
			{
				(*ret)++;
				return (1);
			}
		}
		else if (opt.type == 'D')
		{
			if (opt.conv > 0 && !opt.attri.plus)
			{
				(*ret)++;
				return (1);
			}
		}
	}
	return (0);
}

static void	deal_opt(t_opt opt, int *ret)
{
	if (print_opt_space(opt, ret))
		ft_putchar(' ');
	else if (print_moins(opt, ret))
		ft_putchar('-');
	else if (print_plus(opt, ret))
		ft_putchar('+');
}

int		print_space_left(t_opt opt)
{
	int	size;
	int	ret;

	ret = 0;
	size = opt.width - nbrlen(opt);
	if ((ft_check_charset(opt.type, "di") && (int)opt.conv < 0)
		|| (opt.type == 'D' && opt.conv < 0)
		|| (ft_check_charset(opt.type, "diDuU") && opt.attri.plus))
			size--;
	size -= print_prefix(opt, 0);
	if ((!opt.attri.moins && opt.presi)
			|| (!opt.attri.moins && !opt.attri.zero && !opt.presi))
	{
		while (size > 0)
		{
			ft_putchar(' ');
			ret++;
			size--;
		}
	}
	deal_opt(opt, &ret);
	return (ret);
}