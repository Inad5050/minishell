/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:35:05 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 20:05:13 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	m_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strstr(char *hay, char *ndle)
{
	int	i;
	int	j;

	i = 0;
	if (!ndle)
		return (hay);
	while (hay[i])
	{
		j = 0;
		while (hay[i + j] == ndle[j] && hay[i + j])
			j++;
		if (!ndle[j])
			return (&hay[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
		i++;
	if (i < n)
		n = i;
	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		ptr[i] = (char)str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	m_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
