/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:56 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 19:44:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_mini	*init_struct(char **envp)
{
	t_mini	*m;
	int		i;

	m = ft_calloc(1, sizeof(t_mini));
	if (!m)
		return (perror("Couldn't allocate memory in init_struct"), NULL);
	i = 0;
	while (envp[i])
		i++;
	m->envp = ft_calloc(i + 1, sizeof(char *));
	if (!m->envp)
		m_exit("Couldnt allocate memory for m->envp", m);
	m->envp[i] = NULL;
	init_struct_envp(envp, m);
	return (m);
}

void	init_struct_envp(char **envp, t_mini *m)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			j++;
		m->envp[i] = ft_calloc(j + 1, sizeof(char));
		if (!m->envp[i])
			m_exit("Couldnt allocate memory for m->envp[i]", m);
		j = 0;
		while (envp[i][j])
		{
			m->envp[i][j] = envp[i][j];
			j++;
		}
		m->envp[i][j] = '\0';
		i++;
	}
	envp[i] = NULL;
}
