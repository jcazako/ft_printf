#include "ft_printf.h"

void	putchar_nbr(char nbr)
{
	if (nbr < 0)
		nbr *= -1;
	if (nbr > 9)
	{
		putchar_nbr(nbr / 10);
		putchar_nbr(nbr % 10);
	}
	else
		ft_putchar('0' + nbr);
}
