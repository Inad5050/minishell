/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:26:30 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/01 13:58:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_commands(t_mini *m) //comprueba si el command es built_in, si lo es lo indica en is_builtin. Si no lo es comprueba si es uno de los comandos del sistema. Si lo es copia su ruta en full_path. Si no se da ninguno de los dos casos se considera que el comando no es valido.
{
	int	i;
	int	index;

	i = 0;
	get_envp_cmd_dirs(m);
	while (i < m->cmd_count)
	{
		if (is_builtin_alt(m->cmds[i].full_cmd[0]))
			m->cmds[i].is_builtin = 1;
		else
		{
			index = get_cmd_path(m->cmds[i].full_cmd[0], m); //si la funcion NO es built_in, consigue el path a la funcion y lo copia en full_path dentro de la estructura t_command que corresponda		
			if (index)
				m->cmds[i].full_path = ft_strdup(m->cmd_dirs[index]);
			else
				return (m_error("Incorrect command", m), 0);
			if (!sum_path_to_cmd(&(m->cmds[i]), m))
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_builtin_alt(char *cmd)
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

void	get_envp_cmd_dirs(t_mini *m)
{
	char	*dirs;
	
	dirs = return_envp_var("PATH=", m);
	m->cmd_dirs = ft_split(dirs, ':');
	free(dirs);
	if (!m->cmd_dirs)
		m_exit("Couldn't allocate memory in get_envp_cmd_dirs", m);	
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
	tmp_full_path = ft_strdup(cmd_plus_path); //queremos que full_path tenga memoria aparte de full_cmd[0]
	if (!tmp_full_path)
		return (m_exit("Couldn't alloc in sum_path_to_cmd", m), 0);
	tmp = c->full_path;
	c->full_path = tmp_full_path;
	free(tmp);
	free(cmd_plus_slash);
	return (1);	
}
