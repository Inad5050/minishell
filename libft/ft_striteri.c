/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:55:10 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 18:54:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* void	uppercase(unsigned int i, char *s)
{
	if ('a' <= s[i] && s[i] <= 'z')
		s[i] -= ('a' - 'A');
}

int	main(void)
{
	char			*s = NULL;
	unsigned int	i = 0;

	ft_striteri(s, &uppercase);
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	write (1, "\n", 1);
	return (0);
} */
