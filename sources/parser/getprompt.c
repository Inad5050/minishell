/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:46 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/28 20:20:40 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	getprompt(t_mini *m)
{
	char	*user;
	char	*sufix;

	user = return_envp_var("USER=", m);
	if (!user)
	{
		m->prompt = ft_strdup("guest@minishell $ ");
		if (!m->prompt)
			return (m_exit("Cannot allocate memory in getprompt", m), 0);
	}
	else
	{
		sufix = ft_strdup("@minishell $ ");
		if (!sufix)
			return (free(user), m_exit("Cannot allocate memory in getprompt", m), 0);
		m->prompt = ft_strjoin(user, sufix);
		free(user);
		free(sufix);	
		if (!m->prompt)
			return (m_exit("Cannot allocate memory in getprompt 3", m), 0);
	}
	return (1);
}
