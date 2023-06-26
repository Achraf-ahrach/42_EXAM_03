#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void	putnbr(int *cont, int i)
{
	char	p[11] = "0123456789";

	if (i == -2147483648)
	{
		*cont += write(1, "-2147483648", 11);
		return ;
	}
	else if (i < 0)
	{
		*cont += write(1, "-", 1);
		i *= -1;
	}
	if (i <= 9)
		*cont += write(1, &p[i], 1);
	else
	{
		putnbr(cont, i / 10);
		putnbr(cont, i % 10);
	}
}

void	ft_putstr(int *cont, char *str)
{
	int i = 0;

	if (!str)
		*cont += write (1, "(null)", 6);
	while (str && str[i])
	{
		*cont += write(1, &str[i], 1);
		i++;
	}
}

void	ft_puthex(int *cont, unsigned int i)
{
	char p[17] = "0123456789abcdef";

	if (i < 16)
		*cont += write(1, &p[i], 1);
	else
	{
		ft_puthex(cont, i / 16);
		ft_puthex(cont, i % 16);
	}
}

void	ft_param(char str, int *cont, va_list p)
{
	if (str == 'd')
		putnbr(cont, va_arg(p ,int));
	else if (str == 's')
		ft_putstr(cont, va_arg(p, char *));
	else if (str == 'x')
		ft_puthex(cont, va_arg(p, unsigned int));
	else
		*cont += write(1, &str, 1); 
}

int ft_printf(const char *str, ... )
{
	va_list	p;
	int		cont;

	cont = 0;
	va_start(p, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			ft_param(*str, &cont, p);
		}
		else if (*str != '%')
			cont += write (1, str, 1);
		str++;
	}
	va_end(p);
	return (cont);
}
