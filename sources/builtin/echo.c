/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:23:26 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 13:38:29 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_n(char **full_cmd)
{
    return (full_cmd[1] && ft_strcmp(full_cmd[1], "-n") == 0);
}

void echo(t_command *cmd, int outfile)
{
    int i = 1; 
    bool newline = true; 

    if (cmd->full_cmd[i] && strcmp(cmd->full_cmd[i], "-n") == 0)
    {
        newline = false;
        i++;
    }
    while (cmd->full_cmd[i])
    {
        ft_dprintf(outfile, "%s", cmd->full_cmd[i]);          // I modified the printf with a ft_dprintf !! 
        if (cmd->full_cmd[i + 1])
            ft_dprintf(outfile, " ");
        i++;
    }
    if (newline)
        ft_dprintf(outfile, "\n");
}
