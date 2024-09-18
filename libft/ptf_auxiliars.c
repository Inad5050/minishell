/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_auxiliars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:14:56 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 11:50:37 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ptf_putnbr(int n, int count);
int	ptf_putnbr_u(unsigned int n, int count);

/* putnbr with integer output */

int	ptf_putnbr(int n, int count)
{
	char	digit;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		count = ptf_putnbr(n * -1, count);
		count += 1;
	}
	else if (n > 9)
	{
		count = ptf_putnbr(n / 10, count);
		count = ptf_putnbr(n % 10, count);
	}
	else if (n <= 9)
	{
		digit = n + '0';
		write(1, &digit, 1);
		count += 1;
	}
	return (count);
}

/* putnbr for unsigned with integer output */

int	ptf_putnbr_u(unsigned int n, int count)
{
	char	digit;

	if (n > 9)
	{
		count = ptf_putnbr(n / 10, count);
		count = ptf_putnbr(n % 10, count);
	}
	else if (n <= 9)
	{
		digit = n + '0';
		write(1, &digit, 1);
		count += 1;
	}
	return (count);
}
