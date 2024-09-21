/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:33:51 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/20 16:05:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_envp_variable(char *str, int size, t_mini *m) //busca una string que empiece por str (por ejemplo "PATH=") en envp, size es el tamaño de la string que le has pasado (para "PATH=" size = 5)
{
	int		i;
	
	i = 0;
	while (m->envp[i])
	{
		if (ft_strncmp(m->envp[i], str, size))
			return (i);
		i++;
	}
	return (-1);
}
