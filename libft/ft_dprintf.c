/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:28:55 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 13:32:18 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


#define NUM "0123456789"
#define HEX1 "0123456789abcdef"
#define HEX2 "0123456789ABCDEF"

static int	decimal_print(int fd, long int nbr, char *base)
{
	if (nbr < 0)
		return (write(fd, "-", 1) + decimal_print(fd, nbr * (-1), base));
	if (nbr > 9)
		return (decimal_print(fd, nbr / 10, base) + write(fd, &base[nbr % 10], 1));
	return (write(fd, &base[nbr % 10], 1));
}

static int	hexa_print(int fd, unsigned long nbr, char *base)
{
	if (nbr > 15)
		return (hexa_print(fd, nbr / 16, base) + write(fd, &base[nbr % 16], 1));
	return (write(fd, &base[nbr % 16], 1));
}

static int	str_print(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (str_print(fd, "(null)"));
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}

static int	args_check(int fd, char c, va_list va)
{
	if (c == 'c')
		return (write(fd, &(char){va_arg(va, int)}, 1));
	if (c == 's')
		return (str_print(fd, va_arg(va, char *)));
	if (c == 'p')
	{
		write(fd, "0x", 2);
		return (2 + hexa_print(fd, va_arg(va, unsigned long), HEX1));
	}
	if (c == 'd' || c == 'i')
		return (decimal_print(fd, va_arg(va, int), NUM));
	if (c == 'u')
		return (decimal_print(fd, va_arg(va, unsigned int), NUM));
	if (c == 'x')
		return (hexa_print(fd, va_arg(va, unsigned int), HEX1));
	if (c == 'X')
		return (hexa_print(fd, va_arg(va, unsigned int), HEX2));
	return (write(fd, &c, 1));
}

int	ft_dprintf(int fd, char const *s, ...)
{
	int		n;
	va_list	va;

	n = 0;
	va_start(va, s);
	while (*s)
	{
		if (*s == '%')
			n += args_check(fd, *++s, va);
		else
			n += write(fd, s, 1);
		s += !(!*s);
	}
	va_end(va);
	return (n);
}
