/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:06 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/03 00:51:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void handle_input_redirectionn(t_command *cmd, t_mini *mini)
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
static void handle_output_redirectionn(t_command *cmd, t_mini *mini)
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

// Handle input redirection from previous pipe
static void handle_pipe_input(int prev_fd, t_mini *mini)
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
static void handle_pipe_output(t_command *cmd, int pipes[2], t_mini *mini)
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

// Close and clean up pipe ends in the parent process
static void parent_cleanup(int prev_fd, int pipes[2])
{
    if (prev_fd != STDIN_FILENO)
        close(prev_fd);
    close(pipes[1]);
}

// Create a new pipe
static int create_pipe(int pipes[2], t_mini *mini)
{
    if (pipe(pipes) == -1)
    {
        m_err("Pipe creation failed", 1, mini);
        return (-1);
    }
    return (0); 
}

static void setup_and_fork(t_command *cmd, int prev_fd, int pipes[2], t_mini *mini)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        m_error("Fork failed", mini);
        g_status = 1;
        return;
    }
    else if (pid == 0)
    {
        handle_pipe_input(prev_fd, mini);
        if (cmd->next)
            handle_pipe_output(cmd, pipes, mini);

        handle_input_redirectionn(cmd, mini);
        handle_output_redirectionn(cmd, mini);
        if (cmd->is_builtin)
        {
            g_status = handle_builtin(mini);
            exit(g_status);
        }
        else
        {
            execute_command(cmd, mini);
            exit(EXIT_FAILURE);
        }
    }
}


// Main function to handle multiple commands
void handle_multiple_command(t_mini *mini)
{
    t_command *cmd = mini->cmds;
    int pipes[2];
    int prev_fd = STDIN_FILENO;

    while (cmd)
    {
        if (cmd->next)
        {
            if (create_pipe(pipes, mini) == -1) // Create a new pipe
                return;
        }
        
        setup_and_fork(cmd, prev_fd, pipes, mini);
        
        // Update previous fd and close pipe ends in parent
        parent_cleanup(prev_fd, pipes);
        prev_fd = pipes[0];
        
        cmd = cmd->next;
    }

    // Wait for all child processes to complete
    int status;
    while (wait(&status) > 0)
        g_status = WEXITSTATUS(status); // Set g_status based on last command's exit code
}
