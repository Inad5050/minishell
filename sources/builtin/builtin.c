/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:33:22 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/25 10:50:41 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmds;

	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0]) 			// Ensure the command exists
		return;
	if (ft_strcmp(cmd->full_cmd[0], "cd") == 0)					// Check if the command is "cd" and execute the `cd` function with its first argument
		return (cd(cmd->full_cmd[1], cmd->outfile));
	else if (ft_strcmp(cmd->full_cmd[0], "pwd") == 0)			// If the command is "pwd", execute `pwd` and pass the output file descriptor
		return (pwd(cmd->outfile));
	else if (ft_strcmp(cmd->full_cmd[0], "export") == 0)		// For "export", pass the first argument and the output file descriptor
		return (export(cmd->full_cmd[1], cmd->outfile));
	else if (ft_strcmp(cmd->full_cmd[0], "env") == 0)			// If "env" is the command, execute `env` with the output file descriptor
		return (env(mini), cmd->outfile); 
	else if (ft_strcmp(cmd->full_cmd[0], "echo") == 0)			// If the command is "echo", call the `echo` function
		return (echo(cmd, cmd->outfile));						// + cmd->outfile to make the dprintf !! 
	else if (ft_strcmp(cmd->full_cmd[0], "unset") == 0)			// Handle the "unset" command by passing the first argument
		return (unset(cmd->full_cmd[1]));						
	return;														// If no built-in command matches, do nothing
}
