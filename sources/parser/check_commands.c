/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:26:30 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/28 18:53:26 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_commands(t_mini *m) //comprueba si el command es built_in, si lo es lo indica en is_builtin. Si no lo es comprueba si es uno de los comandos del sistema. Si lo es copia su ruta en full_path. Si no se da ninguno de los dos casos se considera que el comando no es valido.
{
	int	i;
	int	index;

	i = 0;
	while (i < m->cmd_count)
	{
		if (is_builtinn(m->cmds[i].full_cmd[0]))
			m->cmds[i].is_builtin = 1;
		else
		{
			index = get_cmd_path(m->cmds[i].full_cmd[0], m); //si la funcion NO es built_in, consigue el path a la funcion y lo copia en full_path dentro de la estructura t_command que corresponda		
			if (index)
				m->cmds[i].full_path = ft_strdup(m->cmd_dirs[index]);
			else
				return (m_error("Incorrect command", m), 0);
		}
		i++;
	}
	return (1);
}

int	is_builtinn(char *cmd)
{
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

char	*cmd_path(char **cmd_name, t_mini *m)
{
	char	*cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_strjoin("/", cmd_name[0]);
	if (!cmd)
		return (NULL);
	while (i < m->cmd_count)
	{
		path = ft_strjoin(m->cmd_dirs[i], cmd);
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