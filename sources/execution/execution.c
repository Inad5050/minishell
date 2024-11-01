/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:03 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/31 19:03:38 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

int	is_builtin(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmds; 
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
		return (0);
	if (ft_strcmp(cmd->full_cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->full_cmd[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->full_cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->full_cmd[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->full_cmd[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->full_cmd[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->full_cmd[0], "exit") == 0)
		return (1);
	return (0);
}

static int handle_builtin(t_mini *mini)
{
	if (is_builtin(mini))
	{
		builtin(mini);
		return 1;
	}
	return 0;
}

static int handle_single_command(t_mini *mini)
{
	t_command *cmd = mini->cmds;

	if (cmd->next == NULL)
	{
		execute_single_command(mini);
		return 1;
	}
	return 0;
}

void analizing_command(t_mini *mini)
{	
    t_command *cmd = mini->cmds;

    if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
    {
        m_error("Error: No command provided", mini);
        return;
    }

    if (cmd->next == NULL) // Single command
    {
        if (handle_builtin(mini) || handle_single_command(mini))
            return;
    }
    else // Pipeline (multiple commands)
    {
        handle_multiple_command(mini);
    }
}
