/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:03 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 16:19:59 by otboumeh         ###   ########.fr       */
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
	if (is_builtin(mini))
		builtin(mini);
	else if (cmd->next == NULL)  // Check if there's only one command
		execute_single_command(mini);
	else
	{
		while (cmd->next)
			i++;	
		pipe_command(mini, i);
	}
}