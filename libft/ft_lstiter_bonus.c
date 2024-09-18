/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:04:41 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/29 17:21:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

/* void	capitalize(void *str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = ft_strdup(char *)str;
	while (str2[i])
	{
		if ('a' <= str2[i] && str2[i] <= 'z')
			str2[i] = str2[i] - ('A' - 'a');
		i++;
	}
}

int	main(void)
{
	t_list	*node1 = ft_lstnew("hola");

	printf("%s\n", node1->content);
	ft_lstiter(node1, &capitalize);
	printf("%s\n", node1->content);
	return (0);
} */
