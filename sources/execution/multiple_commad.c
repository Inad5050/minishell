/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:06 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/25 11:13:18 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_pipe_input(int prev_fd, t_mini *mini)
{
    if (prev_fd != STDIN_FILENO)
    {
        if (dup2(prev_fd, STDIN_FILENO) == -1)
        {
            m_error("Input redirection failed", mini);
            exit(EXIT_FAILURE);
        }
        close(prev_fd);
    }
}

static void handle_pipe_output(t_command *cmd, int pipes[2], t_mini *mini)
{
    if (cmd->next)
    {
        if (dup2(pipes[1], STDOUT_FILENO) == -1)
        {
            m_error("Output redirection failed", mini);
            exit(EXIT_FAILURE);
        }
        close(pipes[1]);
    }
}

static void parent_cleanup(int prev_fd, int pipes[2])
{
    if (prev_fd != STDIN_FILENO)
        close(prev_fd);
    close(pipes[1]);
}

static int create_pipe(int pipes[2], t_mini *mini)
{
    if (pipe(pipes) == -1)
    {
        m_error("Pipe failed", mini);
        return (-1);
    }
    return (0); 
}

static void fork_and_execute(t_command *cmd, int prev_fd, int pipes[2], t_mini *mini)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        m_error("Fork failed", mini);
        return;
    }
    else if (pid == 0)
    {
        handle_pipe_input(prev_fd, mini);
        handle_pipe_output(cmd, pipes, mini);
        handle_input_redirection(cmd, mini);
        handle_output_redirection(cmd, mini);
        execute_command(cmd, mini);
        exit(EXIT_FAILURE); // In case execve fails
    }
}

void handle_multiple_command(t_mini *mini)
{
    t_command *cmd = mini->cmds;
    int pipes[2];
    int prev_fd = STDIN_FILENO;

    while (cmd)
    {
        if (cmd->next)
        {
            if (create_pipe(pipes, mini) == -1) // Check for pipe creation success
                return;
        }
        fork_and_execute(cmd, prev_fd, pipes, mini);
        parent_cleanup(prev_fd, pipes); // Clean up the parent process
        prev_fd = pipes[0];
        cmd = cmd->next;
    }
}
