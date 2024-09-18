/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:45:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/10 16:14:55 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)b;
	while (len)
	{
		*temp = (unsigned char)c;
		len--;
		temp++;
	}
	return (b);
}

/* int	main(void)
{
	size_t	len = 5;
	char	*str = (char *)malloc(len * sizeof(char));

	printf("%s\n", ft_memset(str, '5', len));
	return (0);
} */
