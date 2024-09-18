/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:28:14 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/29 14:39:52 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		i;

	current = lst;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/* int	main(void)
{
	t_list	*list = NULL;
	t_list	*nodo1 = ft_lstnew("nodo1");
	ft_lstadd_front(&list, nodo1);
	t_list	*nodo2 = ft_lstnew("nodo2");
	ft_lstadd_front(&list, nodo2);
	printf("%d\n", ft_lstsize(list));
	return (0);
} */
