/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:03 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/03 16:35:45 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

int is_builtin(char *cmd_str) {
    if (ft_strcmp(cmd_str, "cd") == 0) 
		return 1;
    if (ft_strcmp(cmd_str, "pwd") == 0) 
		return 1;
    if (ft_strcmp(cmd_str, "export") == 0) 
		return 1;
    if (ft_strcmp(cmd_str, "env") == 0) 
		return 1;
    if (ft_strcmp(cmd_str, "echo") == 0) 
		return 1;
    if (ft_strcmp(cmd_str, "unset") == 0) 
		return 1;
    if (ft_strcmp(cmd_str, "exit") == 0) 
		return 1;
    return 0;
}

int handle_builtin(t_mini *mini) {
    // Get the command from the mini structure
    t_command *cmd = mini->cmds;

    // Check if the command exists and is built-in
    if (cmd && is_builtin(cmd->full_cmd[0])) {
        return builtin(mini); // Execute the built-in command and return its status
    }
    return 0; // Return 0 if not a built-in command
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
        m_err("Error: No command provided", 127, mini);
        return;
    }
    if (cmd->next == NULL && is_builtin(cmd->full_cmd[0])) // Single built-in command
    {
        g_status = builtin(mini); // Directly execute and set the status
        return;
    }
    else if (cmd->next == NULL) // Single non-built-in command
    {
        if (handle_single_command(mini))
        {
          return;
        }
    }
    else // Multiple commands (pipeline)
    {
        handle_multiple_command(mini);
    }
}