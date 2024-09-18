/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:12:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 19:08:42 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	src_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	while (src[src_len] && (dest_len + src_len + 1) < size)
	{
		dest[dest_len + src_len] = src[src_len];
		src_len++;
	}
	if (dest_len < size)
		dest[dest_len + src_len] = '\0';
	return (dest_len + ft_strlen(src));
}

/* int	main(void)
{
	char	dest[] = "ola que tal";
	char	src[] = "como vamos";
	size_t	size = 22;

	printf("%n\n", ft_strlcat(dest, src, size));
	printf("%s\n", dest);
	return (0);
} */
