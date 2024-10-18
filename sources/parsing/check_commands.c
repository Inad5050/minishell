/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:26:30 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/18 17:05:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_commands(t_mini *m) //comprueba si el command es built_in, si lo es lo indica en is_builtin. Si no lo es comprueba si es uno de los comandos del sistema. Si lo es copia su ruta en full_path. Si no se da ninguno de los dos casos se considera que el comando no es valido.
{
	int	i;
	int	index;

	i = 0;
	while (m->cmds[i])
	{
		if (is_builtin(m->cmds[i].full_cmd[0], m))
			m->cmds[i].is_builtin = 1;
		else
		{
			index = get_cmd_path(m->cmds[i].full_cmd[0], m)
			if (index)
				m->cmds[i].full_path = ft_strdup(m->cmd_dirs[index]);
			else
				m_error("Incorrect command", m);
		}
		i++;
	}
}

int	is_builtin(char *cmd, t_mini *m)
{
	if (!cmd)
		m_error("Missing command", m);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	get_cmd_path(char *cmd_name, t_mini *m)
{
	char	*cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_strjoin("/", cmd_name);
	if (!cmd)
		return (0);
	while (m->cmd_dirs[i])
	{
		path = ft_strjoin(m->cmd_dirs[i], cmd);
		if (!path)
			return (0);
		if (!(access(path, X_OK)))
			return (free(cmd), i);
		free(path);
		i++;
	}
	free(cmd);
	return (0);	
}

char	*cmd_path(char **cmd_name, t_pipex *p)
{
	char	*cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_strjoin("/", cmd_name[0]);
	if (!cmd)
		return (NULL);
	while (p->dirs[i])
	{
		path = ft_strjoin(p->dirs[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
		{
			free(cmd);
			return (path);
		}
		free(path);
		i++;
	}
	free(cmd);
	return (NULL);
}