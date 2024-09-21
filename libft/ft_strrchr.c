/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:48:19 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/27 12:52:16 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == (char)character)
			result = (char *)&str[i];
		i++;
	}
	if (str[i] == (char)character)
		result = (char *)&str[i];
	return (result);
}

/* int	main(void)
{
	const char	str[] = "ola que5 tal";
	int			character = 0;

	if (ft_strrchr(str, character) != NULL)
		printf("%s\n", ft_strrchr(str, character));
	return (0);
} */
