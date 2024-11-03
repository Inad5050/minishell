/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:33:22 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/03 13:53:46 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	builtin(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmds;
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
		return (0);
	if (ft_strcmp(cmd->full_cmd[0], "cd") == 0)
		return (builtin_cd(cmd, mini));
	else if (ft_strcmp(cmd->full_cmd[0], "pwd") == 0)
		return (built_pwd(cmd->outfile));
	else if (ft_strcmp(cmd->full_cmd[0], "export") == 0)
		return (export_var(cmd->full_cmd[1], cmd->outfile, mini));
	else if (ft_strcmp(cmd->full_cmd[0], "env") == 0)
		return (env(mini, cmd->outfile));
	else if (ft_strcmp(cmd->full_cmd[0], "echo") == 0)
		return (echo(cmd, cmd->outfile));
	else if (ft_strcmp(cmd->full_cmd[0], "unset") == 0)
		return (unset(cmd, mini));
	else if (ft_strcmp(cmd->full_cmd[0], "exit") == 0)
		return (exit_builtin(cmd, mini));
	return (1);
}

int	execute_builtin_in_pipe(t_command *cmd, t_mini *mini)
{
	int	saved_stdout;
	int	status;

	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			m_err("Output redirection failed", 1, mini);
			return (1);
		}
	}
	status = builtin(mini);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (status);
}
