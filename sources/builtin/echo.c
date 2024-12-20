/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:23:26 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/04 22:46:13 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo(t_command *cmd, int outfile)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
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
