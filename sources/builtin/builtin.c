/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:33:22 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/27 19:47:38 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

void builtin(t_mini *mini)
{
    t_command *cmd;

    cmd = mini->cmds;

    if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
        return;

    if (ft_strcmp(cmd->full_cmd[0], "cd") == 0)
        builtin_cd(cmd, mini);
    else if (ft_strcmp(cmd->full_cmd[0], "pwd") == 0)
        g_status = built_pwd(cmd->outfile, mini->envp);
    else if (ft_strcmp(cmd->full_cmd[0], "export") == 0)
        g_status = export_var(cmd->full_cmd[1], cmd->outfile, mini);
    else if (ft_strcmp(cmd->full_cmd[0], "env") == 0)
        g_status = env(mini, cmd->outfile);
    else if (ft_strcmp(cmd->full_cmd[0], "echo") == 0)
        g_status = echo(cmd, cmd->outfile);
    else if (ft_strcmp(cmd->full_cmd[0], "unset") == 0)
        g_status = unset(cmd, mini);
    else
        g_status = 1;
    return;
}
