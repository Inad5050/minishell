/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:56:18 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/07 12:55:21 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	new_node->next = *lst;
	*lst = new_node;
}

/* int	main(void)
{
	t_list	*lst = NULL;
	t_list	*nodo1 = ft_lstnew("nodo 1");
	ft_lstadd_front(lst, nodo1);
	t_list	*nodo2 = ft_lstnew("nodo 2");
	ft_lstadd_front(lst, nodo2);
	t_list	*new = ft_lstnew("nodo 3");
	ft_lstadd_front(lst, new);
	t_list *current = list;
	while (current)
	{
		printf("%s\n", (*char)current->content);
		current = current->next;
	}
	return (0);
} */
