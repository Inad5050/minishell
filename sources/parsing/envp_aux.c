/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:33:51 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/22 16:41:49 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_envp_variable(char *str, t_mini *m) //busca una string que empiece por str (por ejemplo "PATH=") en envp, size es el tamaño de la string que le has pasado (para "PATH=" size = 5)
{
	int		str_size;
	int		line;
	int		i;
	char	*var;
	
	str_size = 0;
	while (str[str_size])
		str_size++;
	line = find_envp_variable(str, str_size, m);
	if (line < 0)
		return (NULL);
	i = 0;
	while (m->envp[line][i + str_size])
		i++;
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		m_exit("Cannot allocate meemory for envp_variable", m);
	i = -1;
	while (m->envp[line][i++ + str_size])
		var[i] = m->envp[line][i + str_size];
	return (var);
}

int	find_envp_variable(char *str, int size, t_mini *m)
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
