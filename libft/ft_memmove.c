/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:41:09 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 18:22:41 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*c_dest;
	char	*c_src;

	i = 0;
	c_dest = (char *)dest;
	c_src = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (c_src < c_dest && c_dest < c_src + n)
	{
		while (n--)
			c_dest[n] = c_src[n];
	}
	else
	{
		while (i < n)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	}
	return (dest);
}
