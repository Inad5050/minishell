/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:16 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/28 09:48:02 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_input_redirection(t_command *cmd, t_mini *mini)
{
    if (cmd->infile != STDIN_FILENO)
    {
        if (dup2(cmd->infile, STDIN_FILENO) == -1)
        {
            m_error("Input redirection failed", mini);
            exit(EXIT_FAILURE);
        }
        close(cmd->infile);
    }
}

void handle_output_redirection(t_command *cmd, t_mini *mini)
{
    if (cmd->outfile != STDOUT_FILENO)
    {
        if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
        {
            m_error("Output redirection failed", mini);
            exit(EXIT_FAILURE);
        }
        close(cmd->outfile);
    }
}

void execute_command(t_command *cmd, t_mini *mini)
{
    if (execve(cmd->full_path, cmd->full_cmd, mini->envp) == -1)
    {
        m_error("Command execution failed", mini);
        exit(EXIT_FAILURE);
    }
}

void execute_single_command(t_mini *mini)
{
    t_command *cmd = mini->cmds;
    pid_t pid = fork();

    if (pid < 0)
    {
        m_error("Fork failed", mini);
        g_status = 1;  // Set error code for fork failure
        return;
    }
    else if (pid == 0)
    {
        handle_input_redirection(cmd, mini);
        handle_output_redirection(cmd, mini);
        execute_command(cmd, mini);
    }
    else
    {
        if (cmd->infile != STDIN_FILENO)
            close(cmd->infile);
        if (cmd->outfile != STDOUT_FILENO)
            close(cmd->outfile);
        
        int status;
        waitpid(pid, &status, 0);
        g_status = WEXITSTATUS(status);  // Set g_status to child’s exit status
    }
}
