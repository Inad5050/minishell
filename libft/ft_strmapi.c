/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:48 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 18:55:53 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*str;
	unsigned int	i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

/* char	uppercase(unsigned int i, char c)
{
	(void)i;
	if ('a' <= c && c <= 'z')
		c -= ('a' - 'A');
	return (c);
}

int	main(void)
{
	char	*str;
	char const	*s = NULL;

	str = ft_strmapi(s, &uppercase);
	while (*str)
	{
		write (1, str, 1);
		str++;
	}
	write (1, "\n", 1);
	return (0);
} */
