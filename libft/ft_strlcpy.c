/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:22:53 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 19:08:46 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size == 0)
		return (len);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (size)
		dest[i] = '\0';
	return (len);
}

/* int	main(void)
{
	char dest[] = "borramepapi";
	const char src[] = "ola que tal";

	printf("%s\n", src);
	ft_strlcpy(dest, src, 8);
	printf("%s\n", dest);
	strlcpy(dest, src, 8);
	printf("%s\n", dest);
	return (0);
} */
