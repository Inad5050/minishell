/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:23:26 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/27 19:50:06 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int echo(t_command *cmd, int outfile)
{
    int i = 1;
    int newline = 1;

    if (cmd->full_cmd[i] && ft_strcmp(cmd->full_cmd[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (cmd->full_cmd[i])
    {
        write(outfile, cmd->full_cmd[i], ft_strlen(cmd->full_cmd[i]));
        if (cmd->full_cmd[i + 1])
            write(outfile, " ", 1);
        i++;
    }
    if (newline)
        write(outfile, "\n", 1);

    g_status = 0;
    return (g_status);
}
