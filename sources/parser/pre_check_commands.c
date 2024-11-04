/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:01:54 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 19:49:03 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pre_check_commands(t_mini *m)
{
	check_built_in(m);
	if (!check_path_env(m))
		return (0);
	if (!m->no_path)
	{
		if (!get_envp_cmd_dirs(m))
			return (0);
	}
	return (1);
}

void	check_built_in(t_mini *m)
{
	int	i;

	i = 0;
	while (i < m->cmd_count)
	{
		if (is_builtin_alt(m->cmds[i].full_cmd[0]))
			m->cmds[i].is_builtin = 1;
		i++;
	}
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

int	check_path_env(t_mini *m)
{
	int	index;
	int	i;

	m->no_path = 0;
	index = is_path_avaiable("PATH=", 5, m);
	if (index < 0)
		m->no_path = 1;
	if (!(index < 0))
	{
		if (ft_strlen(&(m->envp[index][5])) < 1)
			m->no_path = 1;
	}
	i = 0;
	while (i < m->cmd_count)
	{
		if (m->no_path && (!m->cmds[i].is_builtin || \
		!ft_strcmp(m->cmds[i].full_cmd[0], "env")))
			return (m_err("PATH not avaiable for cmd", 127, m), 0);
		i++;
	}
	return (1);
}

int	is_path_avaiable(char *str, int size, t_mini *m)
{
	int		i;

	i = 0;
	while (m->envp[i])
	{
		if (!ft_strncmp(m->envp[i], str, size))
			return (i);
		i++;
	}
	return (-1);
}
