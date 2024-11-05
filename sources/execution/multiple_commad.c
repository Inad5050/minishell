/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:06 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/05 15:55:22 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input_redirectionn(t_command *cmd, t_mini *mini)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			m_err("Input redirection failed", 1, mini);
			exit(EXIT_FAILURE);
		}
		close(cmd->infile);
	}
}

// Handle output redirection for single command
void	handle_output_redirectionn(t_command *cmd, t_mini *mini)
{
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			m_err("Output redirection failed", 1, mini);
			exit(EXIT_FAILURE);
		}
		close(cmd->outfile);
	}
}

// Close and clean up pipe ends in the parent process
static void	parent_cleanup(int prev_fd, int pipes[2])
{
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	close(pipes[1]);
}

// Create a new pipe
static int	create_pipe(int pipes[2], t_mini *mini)
{
	if (pipe(pipes) == -1)
	{
		m_err("Pipe creation failed", 1, mini);
		return (-1);
	}
	return (0);
}

// Main function to handle multiple commands
void	handle_multiple_command(t_mini *mini)
{
	t_command	*cmd;
	int			pipes[2];
	int			prev_fd;
	int			status;

	cmd = mini->cmds;
	prev_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
		{
			if (create_pipe(pipes, mini) == -1)
				return ;
		}
		s(cmd, prev_fd, pipes, mini);
		parent_cleanup(prev_fd, pipes);
		prev_fd = pipes[0];
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		mini->g_status = WEXITSTATUS(status);
}
