/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:51:13 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 19:09:03 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ndle[0] == '\0')
		return ((char *)hay);
	while (hay[i] && (i < len))
	{
		while (hay[i + j] == ndle[j] && (i + j) < len && hay[i + j])
		{
			j++;
			if (ndle[j] == '\0')
				return ((char *)hay + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	const char *haystack = "ola que tal saludos";
	const char *needle = "tal";
	size_t	len = 30;

	printf("%s\n", ft_strnstr(haystack, needle, len));
	printf("%s\n", strnstr(haystack, needle, len));
	return (0);
} */
