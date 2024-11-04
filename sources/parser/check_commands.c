/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:26:30 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 19:31:57 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_commands(t_mini *m)
{
	int	i;
	int	index;

	i = 0;
	while (i < m->cmd_count)
	{
		if (!m->cmds[i].is_builtin)
		{
			if (!check_cmd_plus_route(i, m))
			{
				index = get_cmd_path(m->cmds[i].full_cmd[0], m);
				if (index)
					m->cmds[i].full_path = ft_strdup(m->cmd_dirs[index]);
				else
					return (m_err("Incorrect command", 127, m), 0);
				if (!sum_path_to_cmd(&(m->cmds[i]), m))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_cmd_plus_route(int i, t_mini *m)
{
	char	*tmp;
	char	*tmp_full_command;

	if ((access(m->cmds[i].full_cmd[0], X_OK)))
		return (0);
	else
	{
		tmp_full_command = ft_strdup(m->cmds[i].full_cmd[0]);
		if (!tmp_full_command)
			return (m_exit("Couldn't alloc in update_full_path", m), 0);
		tmp = m->cmds[i].full_path;
		m->cmds[i].full_path = tmp_full_command;
		free(tmp);
	}
	return (1);
}

int	get_cmd_path(char *cmd_name, t_mini *m)
{
	char	*cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_strjoin("/", cmd_name);
	if (!cmd)
		return (m_exit("Couldn't alloc in get_cmd_path", m), 0);
	while (m->cmd_dirs[i])
	{
		path = ft_strjoin(m->cmd_dirs[i], cmd);
		if (!path)
			return (m_exit("Couldn't alloc in get_cmd_path", m), 0);
		if (!(access(path, X_OK)))
			return (free(cmd), free(path), i);
		free(path);
		i++;
	}
	free(cmd);
	return (0);
}

int	sum_path_to_cmd(t_command *c, t_mini *m)
{
	char	*cmd_plus_slash;
	char	*cmd_plus_path;
	char	*tmp;
	char	*tmp_full_path;

	cmd_plus_slash = ft_strjoin("/", c->full_cmd[0]);
	if (!cmd_plus_slash)
		return (m_exit("Couldn't alloc in sum_path_to_cmd", m), 0);
	cmd_plus_path = ft_strjoin(c->full_path, cmd_plus_slash);
	if (!cmd_plus_path)
		return (m_exit("Couldn't alloc in sum_path_to_cmd", m), 0);
	tmp = c->full_cmd[0];
	c->full_cmd[0] = cmd_plus_path;
	free(tmp);
	tmp_full_path = ft_strdup(cmd_plus_path);
	if (!tmp_full_path)
		return (m_exit("Couldn't alloc in sum_path_to_cmd", m), 0);
	tmp = c->full_path;
	c->full_path = tmp_full_path;
	free(tmp);
	free(cmd_plus_slash);
	return (1);
}
