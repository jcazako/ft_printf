#include "ft_printf.h"
#include <wchar.h>
#include <unistd.h>

static int	check_mask(t_opt opt)
{
	int	size;
 
	if ((int)opt.conv < 0 || opt.conv > 0x10FFFF)
		return (-1);
	size = size_base(opt);
	if (opt.conv <= 0x7F)
		return (MASK_0);
	else if (opt.conv <= 0x7FF)
		return (MASK_1);
	else if (opt.conv <= 0xFFFF)
		return (MASK_2);
	else
		return (MASK_3);
}

static int	select_u_mask(int mask)
{
	if (mask == MASK_0)
		return (U_MASK_0);
	else if (mask == MASK_1)
		return (U_MASK_1);
	else if (mask == MASK_2)
		return (U_MASK_2);
	else if (mask == MASK_3)
		return (U_MASK_3);
	return (0);
}

static void	print_c(long ret)
{
	if (ret > 0x7F)
		print_c(ret >> 8);
	ret &= 0xFF;
	write(1, &ret, 1);
}

static int	deal_c(int mask, t_opt opt)
{
	int	i;
	long	ret;

	i = 0;
	ret = 0;
	if ((mask = check_mask(opt)) == -1)
		return (-1);
	while (i < ft_size_base(mask, 2))
	{
		if (mask & ft_pow(2, i))
		{
			ret |= ((0x1 & opt.conv) << i);
			opt.conv >>= 1;
		}
		i++;
	}
	mask = select_u_mask(mask);
	ret |= mask;
	print_c(ret);
	ret = (mask == (int)U_MASK_0) ? 1 : 0;
	ret = (mask == (int)U_MASK_1) ? 2 : ret;
	ret = (mask == (int)U_MASK_2) ? 3 : ret;
	ret = (mask == (int)U_MASK_3) ? 4 : ret;
	return ((int)ret);
}

int	putlong_char(t_opt opt)
{
	int	mask;
	long	ret;

	ret = 0;
	mask = 0;
	if (opt.type == 'c')
	{
		ft_putchar(opt.conv);
		return (1);
	}
	else if (opt.type == 'C')
		return (deal_c(mask, opt));
	return (0);
}
