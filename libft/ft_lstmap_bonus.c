/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:19:24 by dangonz3          #+#    #+#             */
/*   Updated: 2024/04/30 16:18:21 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*temp;
	void	*p;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		p = f(lst->content);
		temp = ft_lstnew(p);
		if (temp == NULL)
		{
			free(p);
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, temp);
		lst = lst->next;
	}
	return (start);
}

/* No podemos usar temp como argumento de ft_lstclear porque si le pasamos
 un argumento NULL a una funcion tendriamos un segmentation error.
 En lugar de eso usamos start y arrasamos toda la lista. */