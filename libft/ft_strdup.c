/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:29:13 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 19:08:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] != '\0')
		i++;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ptr[i] = (char)str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* int	main(void)
{
	char	str[] = "123fffff456";

	printf("%s\n", ft_strdup(str));
	printf("%s\n", strdup(str));
	return (0);
} */
