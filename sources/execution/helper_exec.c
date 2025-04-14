/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:27:59 by tshiki            #+#    #+#             */
/*   Updated: 2024/11/05 15:55:11 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	c(t_command *cmd, int prev_fd, int pipes[2], t_mini *mini)
{
	handle_pipe_input(prev_fd, mini);
	if (cmd->next)
		handle_pipe_output(cmd, pipes, mini);
	handle_input_redirectionn(cmd, mini);
	handle_output_redirectionn(cmd, mini);
}

void	s(t_command *cmd, int prev_fd, int pipes[2], t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		m_err("Fork failed", 1, mini);
		return ;
	}
	else if (pid == 0)
	{
		c(cmd, prev_fd, pipes, mini);
		run_command(cmd, mini);
	}
}

void	run_command(t_command *cmd, t_mini *mini)
{
	if (cmd->is_builtin)
	{
		mini->g_status = handle_builtin(mini);
		exit(mini->g_status);
	}
	else
	{
		execute_command(cmd, mini);
		exit(EXIT_FAILURE);
	}
}

void	handle_pipe_input(int prev_fd, t_mini *mini)
{
	if (prev_fd != STDIN_FILENO)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			m_err("Input redirection from pipe failed", 1, mini);
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
}

// Handle output redirection to current pipe
void	handle_pipe_output(t_command *cmd, int pipes[2], t_mini *mini)
{
	if (cmd->next)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
		{
			m_err("Output redirection to pipe failed", 1, mini);
			exit(EXIT_FAILURE);
		}
		close(pipes[1]);
	}
}
