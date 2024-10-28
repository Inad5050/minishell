/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:33:22 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/28 09:03:56 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int builtin(t_mini *mini)
{
    t_command *cmd = mini->cmds;

    if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
        return (0);
    if (ft_strcmp(cmd->full_cmd[0], "cd") == 0)
        return (builtin_cd(cmd, mini));
    else if (ft_strcmp(cmd->full_cmd[0], "pwd") == 0)
        return (builtin_pwd(cmd->outfile, mini->envp));
    else if (ft_strcmp(cmd->full_cmd[0], "export") == 0)
        return (export_var(cmd->full_cmd[1], cmd->outfile, mini));
    else if (ft_strcmp(cmd->full_cmd[0], "env") == 0)
        return (env(mini, cmd->outfile));
    else if (ft_strcmp(cmd->full_cmd[0], "echo") == 0)
        return (echo(cmd, cmd->outfile));
    else if (ft_strcmp(cmd->full_cmd[0], "unset") == 0)
        return (unset(cmd, mini));
    else if (ft_strcmp(cmd->full_cmd[0], "exit") == 0)
        return (built_exit(mini->tokens));

    return (1); // return a non-zero status if no valid command was found
}