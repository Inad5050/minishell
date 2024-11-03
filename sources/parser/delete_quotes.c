/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:07:45 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/02 23:28:28 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	delete_quotes(t_mini *m)
{
	int	i;	
	
	i = -1;
	while (++i < m->cmd_count)
	{
		if (!delete_squotes(i, m))
			return (0);
		if (!delete_dquotes(i, m))
			return (0);
	}
	return (1);
}

int	delete_squotes(int i, t_mini *m)
{
	char	*new_str;
	char	*tmp;
	int	x;
	
	x = 0;
	while (m->cmds[i].full_cmd[x])
	{
		if (m->cmds[i].full_cmd[x][0] == '\'' && !(m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\''))
			return (m_err("Invalid quotes", 2, m), 0);
		if (!(m->cmds[i].full_cmd[x][0] == '\'') && m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\'')
			return (m_err("Invalid quotes", 2, m), 0);
		if (m->cmds[i].full_cmd[x][0] == '\'' && m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\'')
		{
			new_str = ft_strtrim(m->cmds[i].full_cmd[x], "\'");
			if (!new_str)
				return (m_exit("Couldn't alloc in delete_squotes", m), 0);
			tmp = m->cmds[i].full_cmd[x];
			m->cmds[i].full_cmd[x] = new_str;
			free(tmp);
		}
		x++;
	}
	return (1);
}

int	delete_dquotes(int i, t_mini *m)
{
	char	*new_str;
	char	*tmp;
	int	x;
	
	x = 0;
	while (m->cmds[i].full_cmd[x])
	{
		if (m->cmds[i].full_cmd[x][0] == '\"' && !(m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\"'))
			return (m_err("Invalid quotes", 2, m), 0);
		if (!(m->cmds[i].full_cmd[x][0] == '\"') && m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\"')
			return (m_err("Invalid quotes", 2, m), 0);
		if (m->cmds[i].full_cmd[x][0] == '\"' && m->cmds[i].full_cmd[x][ft_strlen(m->cmds[i].full_cmd[x]) - 1] == '\"')
		{
			new_str = ft_strtrim(m->cmds[i].full_cmd[x], "\"");
			if (!new_str)
				return (m_exit("Couldn't alloc in delete_squotes", m), 0);
			tmp = m->cmds[i].full_cmd[x];
			m->cmds[i].full_cmd[x] = new_str;
			free(tmp);
		}
		x++;
	}
	return (1);
}
