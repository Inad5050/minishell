/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:46 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 15:24:16 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getprompt(t_mini *m)
{
	int		i;
	int		j;
	char	*str;
	
	j = 0;
	i = find_envp_variable("USER=", 5, m);
	if (i < 0)
	{
		m->prompt = ft_strdup("guest@minishell $ ");
		if (!m->prompt)
			m_exit("Cannot allocate memory for m->prompt", m);
	}
	else
	{
		while (m->envp[i][j + 5])
			j++;
		str = ft_calloc(j + 1, sizeof(char));
		if (!str)
			m_exit("Cannot allocate memory for m->prompt", m);
		j = -1;
		while (m->envp[i][++j + 5])
			str[j] = m->envp[i][j + 5];
		str[j] = '\0';
		m->prompt = ft_strjoin(str, "@minishell $ ");
		free(str);
	}
}

char	*return_envp_variable(char *str, int i, t_mini *m)
{
	int	i;
	i = 0;
	







	
}

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