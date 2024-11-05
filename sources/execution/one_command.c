/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:16 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/05 15:55:27 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input_redirection(t_command *cmd, t_mini *mini)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			m_err("Input redirection failed", 2, mini);
			exit(EXIT_FAILURE);
		}
		close(cmd->infile);
	}
}

void	handle_output_redirection(t_command *cmd, t_mini *mini)
{
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			m_err("Output redirection failed", 2, mini);
			exit(EXIT_FAILURE);
		}
		close(cmd->outfile);
	}
}

void	execute_command(t_command *cmd, t_mini *mini)
{
	if (execve(cmd->full_path, cmd->full_cmd, mini->envp) == -1)
	{
		m_err("Command execution failed", 126, mini);
		exit(EXIT_FAILURE);
	}
}

void	helper_one_command(t_command *cmd, t_mini *mini)
{
	handle_input_redirection(cmd, mini);
	handle_output_redirection(cmd, mini);
	execute_command(cmd, mini);
}

void	execute_single_command(t_mini *mini)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;

	pid = fork();
	cmd = mini->cmds;
	if (pid < 0)
	{
		m_err("Fork failed", 1, mini);
		return ;
	}
	else if (pid == 0)
		helper_one_command(cmd, mini);
	else
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		waitpid(pid, &status, 0);
		mini->g_status = WEXITSTATUS(status);
	}
}
