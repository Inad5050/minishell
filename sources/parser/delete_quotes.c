/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:07:45 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/06 17:08:57 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	delete_quotes(t_mini *m)
{
	int	i;	

	i = 0;
	while (i < m->cmd_count)
	{
		if (!check_export(i, m))
			return (1);
		if (!delete_squotes(i, m))
			return (0);
		if (!delete_dquotes(i, m))
			return (0);
		i++;
	}
	return (1);
}

int	delete_squotes(int i, t_mini *m)
{
	char	*new_str;
	char	*tmp;
	int		x;

	x = -1;
	while (m->cmds[i].full_cmd[++x])
	{
		if (m->cmds[i].full_cmd[x][0] == '\'' && \
		!(m->cmds[i].full_cmd[x][m_len(m->cmds[i].full_cmd[x]) - 1] == '\''))
			return (m_err("Invalid quotes", 2, m), 0);
		if (!(m->cmds[i].full_cmd[x][0] == '\'') && \
		m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\'')
			return (m_err("Invalid quotes", 2, m), 0);
		if (m->cmds[i].full_cmd[x][0] == '\'' && \
		m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\'')
		{
			new_str = ft_strtrim(m->cmds[i].full_cmd[x], "\'");
			if (!new_str)
				return (m_exit("Couldn't alloc in delete_squotes", m), 0);
			tmp = m->cmds[i].full_cmd[x];
			m->cmds[i].full_cmd[x] = new_str;
			free(tmp);
		}
	}
	return (1);
}

int	delete_dquotes(int i, t_mini *m)
{
	char	*new_str;
	char	*tmp;
	int		x;

	x = -1;
	while (m->cmds[i].full_cmd[++x])
	{
		if (m->cmds[i].full_cmd[x][0] == '\"' && \
		!(m->cmds[i].full_cmd[x][m_len(m->cmds[i].full_cmd[x]) - 1] == '\"'))
			return (m_err("Invalid quotes", 2, m), 0);
		if (!(m->cmds[i].full_cmd[x][0] == '\"') && \
		m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\"')
			return (m_err("Invalid quotes", 2, m), 0);
		if (m->cmds[i].full_cmd[x][0] == '\"' && \
		m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\"')
		{
			new_str = ft_strtrim(m->cmds[i].full_cmd[x], "\"");
			if (!new_str)
				return (m_exit("Couldn't alloc in delete_squotes", m), 0);
			tmp = m->cmds[i].full_cmd[x];
			m->cmds[i].full_cmd[x] = new_str;
			free(tmp);
		}
	}
	return (1);
}

int	check_export(int i, t_mini *m)
{
	if (!ft_strcmp(m->cmds[i].full_cmd[0], "export"))
		return (0);
	return (1);
}
