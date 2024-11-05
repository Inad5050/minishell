/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:03 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/05 15:55:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd_str)
{
	if (ft_strcmp(cmd_str, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_str, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_str, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_str, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_str, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_str, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_str, "exit") == 0)
		return (1);
	return (0);
}

int	handle_builtin(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmds;
	if (cmd && is_builtin(cmd->full_cmd[0]))
		return (builtin(mini));
	return (0);
}

static int	handle_single_command(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmds;
	if (cmd->next == NULL)
	{
		execute_single_command(mini);
		return (1);
	}
	return (0);
}

void	analizing_command(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmds;
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		m_err("Error: No command provided", 127, mini);
		return ;
	}
	if (cmd->next == NULL && is_builtin(cmd->full_cmd[0]))
	{
		mini->g_status = builtin(mini);
		return ;
	}
	else if (cmd->next == NULL)
	{
		if (handle_single_command(mini))
		{
			return ;
		}
	}
	else
	{
		handle_multiple_command(mini);
	}
}
