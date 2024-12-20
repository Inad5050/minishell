/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:21:38 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/04 22:56:22 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	var_name_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	return (i);
}

static void	remove_variable(char **my_env, int index)
{
	free(my_env[index]);
	while (my_env[index + 1])
	{
		my_env[index] = my_env[index + 1];
		index++;
	}
	my_env[index] = NULL;
}

static void	do_unset(char *var, t_mini *mini)
{
	int		i;
	int		l;
	char	**my_env;

	my_env = mini->envp;
	l = var_name_len(var);
	i = 0;
	if (!var || strchr(var, '='))
	{
		g_status = 1;
		return ;
	}
	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], var, l) == 0 && my_env[i][l] == '=')
		{
			remove_variable(my_env, i);
			g_status = 0;
			return ;
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "unset: `%s': not found\n", var);
	g_status = 1;
}

int	unset(t_command *cmd, t_mini *mini)
{
	int	i;

	i = 1;
	if (!cmd->full_cmd[1])
	{
		g_status = 1;
		return (g_status);
	}
	while (cmd->full_cmd[i])
	{
		do_unset(cmd->full_cmd[i], mini);
		i++;
	}
	return (g_status);
}
