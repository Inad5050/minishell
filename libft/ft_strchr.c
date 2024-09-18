/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:48:19 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 19:08:15 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, char character)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == character)
			return ((char *)str);
		str++;
	}
	if (character == '\0')
		return ((char *)str);
	return (NULL);
}

/* int	main(void)
{
	const char	*str = "ola que tal";
	const char	*backup = str;
	char	character = 't';

	if (ft_strchr(str, character) != NULL)
		printf("%s\n", ft_strchr(str, character));
	printf("%s\n", strchr(backup, character));
	return (0);
} */
