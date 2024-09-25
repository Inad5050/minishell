/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:03 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/25 10:41:42 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(t_mini *mini)
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

static void handle_builtin(t_mini *mini)
{
	if (is_builtin(mini))
	{
		builtin(mini);
		return;
	}
}

static void handle_single_command(t_mini *mini)
{
	t_command *cmd = mini->cmds;

	if (cmd->next == NULL)
	{
		execute_single_command(mini);
		return;
	}
}

void analizing_command(t_mini *mini)
{	
	t_command *cmd;
	int i;

	i = 0;
	cmd = mini->cmds;
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		m_error("Error: No command provided", mini);
		return;
	}

	handle_builtin(mini);               // Handle built-in commands
	handle_single_command(mini);         // Handle single commands

	while (cmd->next)					// calcul the number of commands
	{
    	cmd = cmd->next;
    	i++;
	}
	handle_multiple_command(mini, i);	//handle multiple commads with pipe				
}

char *get_path_from_env(t_mini *mini)
{
    char *path_var;

    path_var = return_envp_variable("PATH=", mini);
    if (!path_var)
    {
        m_error("Error: PATH not found in environment variables", mini);
        return (NULL);
    }
    return (path_var);
}
