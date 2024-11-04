/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 19:46:43 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_files_aux(char *file, int is_outfile, int i, t_mini *m)
{
	if (!is_outfile)
	{
		if (!(m->cmds[i].append_in))
		{
			m->cmds[i].infile = open(file, O_RDONLY);
			if (m->cmds[i].infile == -1)
				return (m_err("Couldn't open infile", 126, m), 0);
		}
		else if ((m->cmds[i].append_in))
			here_doc(m->cmds[i].infile_name, i, m);
	}
	if (is_outfile)
	{
		if (!(m->cmds[i].append_out))
			m->cmds[i].outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((m->cmds[i].append_out))
			m->cmds[i].outfile = open(file, O_WRONLY | \
			O_CREAT | O_APPEND, 0644);
		if (m->cmds[i].outfile == -1)
			return (m_err("Couldn't open outfile", 126, m), 0);
	}
	return (1);
}

int	open_files(t_mini *m)
{
	int	i;

	i = 0;
	while (i < m->cmd_count)
	{
		if (m->cmds[i].infile_name)
		{
			if (!(open_files_aux(m->cmds[i].infile_name, 0, i, m)))
				return (0);
		}
		if (m->cmds[i].outfile_name)
		{
			if (!(open_files_aux(m->cmds[i].outfile_name, 1, i, m)))
				return (0);
		}
		i++;
	}
	return (1);
}
