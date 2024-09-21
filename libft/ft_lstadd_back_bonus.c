/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:44:55 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/19 16:13:17 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (last == NULL)
		*lst = new_node;
	else
		last->next = new_node;
}

/* int	main(void)
{
	t_list	*lst = NULL;
	t_list	*nodo1 = ft_lstnew("nodo1");
	ft_lstadd_front(&lst, nodo1);
	t_list	*nodo2 = ft_lstnew("nodo2");
	ft_lstadd_front(&lst, nodo2);
	t_list	*nodo3 = ft_lstnew("nodo3");
	t_list	*current = lst;
	while (current)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
	ft_lstadd_back(&lst, nodo3);
	current = lst;
	while (current)
	{
		printf("%s\n", current->content);
		current = current ->next;
	}
} */
