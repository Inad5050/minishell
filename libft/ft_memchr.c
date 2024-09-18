/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:32:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 19:07:56 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		character;

	p = s;
	character = c;
	while (n--)
	{
		if (*p == character)
			return ((void *)p);
		p++;
	}
	return (NULL);
}

/* int	main(void)
{
	unsigned char 	s[] = "ola que nn tal";
	int				c = 110;
	size_t			n = 30;

	if (ft_memchr(s, c, n) != NULL)
		printf("%s\n", ft_memchr(s, c, n));
	return (0);
} */
