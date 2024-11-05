/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:56:25 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/05 15:51:32 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_mini *mini, int outfile)
{
	int	i;

	i = 0;
	if (mini->envp == NULL)
	{
		mini->g_status = 1;
		return (mini->g_status);
	}
	while (mini->envp[i] != NULL)
	{
		dprintf(outfile, "%s\n", mini->envp[i]);
		i++;
	}
	mini->g_status = 0;
	return (mini->g_status);
}
