/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:56:25 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 13:41:23 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_mini *mini, int outfile) 						// change the signature of the focntion to have acces to the outfile
{
	int		i;

	i = 0;
	while (mini->envp[i] != NULL)
	{
		ft_dprintf(outfile, "%s\n", mini->envp[i]); 		// changed to ft_printf !!						
		i++;
	}
}

