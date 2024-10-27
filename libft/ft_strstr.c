/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:39:42 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/27 20:40:10 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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