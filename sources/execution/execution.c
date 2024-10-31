/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:03 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/28 09:47:15 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_command *cmd;
	int i;

	i = 0;
	cmd = mini->cmds;
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
	{
		m_error("Error: No command provided", mini);
		return;
	}
	if(cmd->next == NULL)
	{
	if(handle_builtin(mini))
		return;
	if(handle_single_command(mini))
		return;
	}
	else
		while (cmd->next)
		{
    		cmd = cmd->next;
    		i++;
		}
	handle_multiple_command(mini);	
}

char *get_path_from_env(t_mini *mini)
{
    char *path_var;

    path_var = return_envp_var("PATH=", mini);
    if (!path_var)
    {
        m_error("Error: PATH not found in environment variables", mini);
        return (NULL);
    }
    return (path_var);
}