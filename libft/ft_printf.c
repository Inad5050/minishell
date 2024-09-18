/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:07:24 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 11:49:18 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ptf_selection(char const *s, int i, va_list args);

int	ft_printf(char const *s, ...)
{
	int		count;
	int		i;
	va_list	args;

	count = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			count += ptf_selection(s, i, args);
		}
		else
		{
			write(1, &s[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

int	ptf_selection(char const *s, int i, va_list args)
{
	int	count;

	count = 0;
	if (s[i] == 'd' || s[i] == 'i' || s[i] == 'u')
		count = ptf_print_d(va_arg(args, int), s[i]);
	else if (s[i] == 'x' || s[i] == 'X')
		count = ptf_print_x(va_arg(args, unsigned int), s[i], count);
	else if (s[i] == 's')
		count = ptf_print_s(va_arg(args, char *));
	else if (s[i] == 'c')
		count = ptf_print_c(va_arg(args, int));
	else if (s[i] == '%')
		count = ptf_print_c('%');
	else if (s[i] == 'p')
	{
		count = ptf_print_s("0x");
		count = ptf_print_x(va_arg(args, size_t), s[i], count);
	}
	return (count);
}

/* int	main(void)
{
	int	count;

	printf("FT_PRINTF\n");
	count = ft_printf(" %c %c %c ", 0, '1', '2');
	printf("\ncount = %d\n", count);
	printf("PRINTF\n");
	count = printf(" %c %c %c ", 0, '1', '2');
	printf("\ncount = %d\n", count);
	return (0);
} */
