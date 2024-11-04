/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:13:52 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 19:59:29 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	m_free(char **ptr)
{
	free((void *)*ptr);
	*ptr = NULL;
}

void	free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	while ((*matrix)[i])
	{
		ft_printf("(*matrix)[i] = %s\n", (*matrix)[i]);

		m_free(&(*matrix[i++]));
	}

	ft_printf("*matrix PTR = %p\n", *matrix);
	
	if (*matrix)
	{
		free(*matrix);
		*matrix = NULL;
	}		
}
