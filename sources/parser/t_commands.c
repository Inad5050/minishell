/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_commands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:38:59 by dani              #+#    #+#             */
/*   Updated: 2024/10/31 19:09:46 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	t_commands(t_mini *m)
{
	int	i;
	
	i = 0;
	count_commands(m);
	m->cmds = ft_calloc(m->cmd_count, sizeof(t_command));
	if (!m->cmds)
		m_exit("Couldn't allocate memory in create_t_commands", m);	
	if (!fill_tokens_t_command(m))
		return (0);
	while (i < m->cmd_count)
	{
		m->cmds[i].cmd_index = i;
		m->cmds[i].outfile = 1;
		if (i + 1 < m->cmd_count)
			m->cmds[i].next = &(m->cmds[i + 1]);
		t_commands_fill(&(m->cmds[i]), m);
		i++;
	}
	return (1);
}

void	count_commands(t_mini *m)
{
	int	i;

	m->cmd_count = 1;
	i = 0;
	while (m->tokens[i])
	{
		if (!ft_strcmp(m->tokens[i], "|"))
			m->cmd_count++;
		i++;
	}
}

int	fill_tokens_t_command(t_mini *m)
{
	int	i;
	int	cmd_i;
	int	start;
	
	i = 0;
	cmd_i = 0;
	start = 0;
	while (m->tokens[i])
	{
		if (!ft_strcmp(m->tokens[i], "|"))
		{
			if (!fill_tokens_t_command_aux(i, cmd_i, start, m))
				return (0);
			cmd_i++;
			start = i + 1;			
		}
		i++;
	}
	if (!fill_tokens_t_command_aux(i, cmd_i, start, m))
		return (0);
	return (1);
}

int	fill_tokens_t_command_aux(int i, int cmd_i, int start, t_mini *m)
{
	int x;
	
	x = 0;	
	m->cmds[cmd_i].tokens = ft_calloc(i - start + 1, sizeof(char *));
	if (!m->cmds[cmd_i].tokens)
		return (m_exit("Cannot alocate memory in split_tokens_par 1", m), 0);
	while (start + x < i)
	{
		m->cmds[cmd_i].tokens[x] = ft_strdup(m->tokens[start + x]);
		if (!m->cmds[cmd_i].tokens[x])
			return (m_exit("Cannot alocate memory in split_tokens_par 2", m), 0);
		x++;
	}
	m->cmds[cmd_i].tokens[x] = NULL;
	return (1);
}
