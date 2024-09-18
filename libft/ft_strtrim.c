/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:19:16 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/10 16:16:10 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_anihilate(char *set, char s);
char	*ft_strtostr(char *result, char const *s1, size_t end, size_t start);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	start = 0;
	end = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_anihilate((char *)set, s1[start]) == 1 && s1[start])
		start++;
	while (s1[end])
		end++;
	while (ft_anihilate((char *)set, s1[end - 1]) == 1 && end > start)
		end--;
	result = (char *)malloc((end - start + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result = ft_strtostr(result, s1, end, start);
	return (result);
}

int	ft_anihilate(char *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtostr(char *result, char const *s1, size_t end, size_t start)
{
	char	*str;
	size_t	i;

	i = 0;
	while (start < end)
	{
		result[i] = s1[start];
		start++;
		i++;
	}
	result[i] = '\0';
	str = result;
	return (str);
}

/* int	main(void)
{
	char	*result = ft_strtrim("lorem \n ipsum \t dolor \n sit \t amet", " ");

	while (*result)
	{
		write(1, result, 1);
		result++;
	}
	return (0);
} */
