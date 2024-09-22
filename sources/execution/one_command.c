/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:16 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 16:21:04 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_input_redirection(t_command *cmd, t_mini *mini)
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

static void handle_output_redirection(t_command *cmd, t_mini *mini)
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

static void execute_command(t_command *cmd, t_mini *mini)
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
        wait(NULL);
    }
}
