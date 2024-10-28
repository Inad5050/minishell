/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:56:25 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/27 19:47:25 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int env(t_mini *mini, int outfile)
{
    int i = 0;

    if (mini->envp == NULL)
    {
        g_status = 1;
        return (g_status);
    }
    while (mini->envp[i] != NULL)
    {
        dprintf(outfile, "%s\n", mini->envp[i]);
        i++;
    }
    g_status = 0;
    return (g_status);
}
