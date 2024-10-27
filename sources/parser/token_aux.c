/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:29:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/27 19:29:43 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initiate_command_structs(t_mini *m) //su objetivo es alojar memoria para cada m->cmds[].full_cmd.
{
	int	i;
	int	cmd_index;
	int start;

	i = 0;
	cmd_index = 0;
	start = 0;
	while (m->tokens[i])
	{	
		if (!ft_strcmp(m->tokens[i], "|")) //si hemos encontrado un pipe
		{
			m->cmds[cmd_index].full_cmd = ft_calloc(i - start, sizeof(char *));
			if (cmd_index + 1 < m->cmd_count)
				m->cmds[cmd_index].next = &(m->cmds[cmd_index + 1]);
			else
				m->cmds[cmd_index].next = NULL;
			cmd_index++;
			start = i + 1; //el proximo full_cmd para siguiente command no empezara con '|' sino con el siguiente token
		}
		i++;
	}
	m->cmds[cmd_index].full_cmd = ft_calloc(i - start, sizeof(char *));
}

void	initiate_get_commands(t_mini *m) //consigue los valores de m->path y m->cmd_dirs. Aloja meoria para m->cmds.
{
	int	i;
	int	x;
	
	m->path = return_envp_var("PATH=", m);	
	m->cmd_dirs = ft_split(m->path, ':');
	if (!m->cmd_dirs)
		m_exit("Cannot allocate memory in initiate_get_commands", m);	
	i = 0;
	m->cmd_count = 1; //minimo tenemos un comando
	m->x_index = 0;
	while (m->tokens[i])
	{
		x = 0;
		while (m->tokens[i][x])
		{
			if (m->tokens[i][x++] == '|')
				m->cmd_count++; //por cada pipe que encontramos tendremos un comando adicional.
		}
		i++;
	}
	m->cmds = ft_calloc(m->cmd_count, sizeof(t_command)); //m->cmds apuntara a cada estructura asociada con un comando.
	if (!m->cmds)
		m_exit("Cannot allocate memory in initiate_commands", m);
}
