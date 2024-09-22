/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:56:25 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/21 15:35:34 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->envp[i] != NULL)
	{
		printf("%s\n", mini->envp[i]); 		// Maybe we will need dprintf ????? later when we compilate we will see the difference !!!!							
		i++;
	}
}

