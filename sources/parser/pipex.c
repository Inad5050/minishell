/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:49:56 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/03 00:17:32 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipex(t_mini *m)
{
	int	i;
	
	i = 0;
	while (i < m->cmd_count - 1)
	{
		if (!m->cmds[i].outfile_name && !m->cmds[i + 1].infile_name)
		{
			if (!redirect_pipe(&(m->cmds[i]), &(m->cmds[i + 1]), m))
				return (0);
		}
		i++;
	}
	return (1);
}

int	redirect_pipe(t_command *c1, t_command *c2, t_mini *m)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		return (m_err("Couldn't pipe in redirect_pipe", 1, m), 0);
	c1->outfile = pipefd[1];
	c2->infile = pipefd[0];	
	return (1);
}
