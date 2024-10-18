/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:46 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/18 18:06:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	getprompt(t_mini *m)
{
	char	*user;
	char	*sufix;

	user = return_envp_variable("USER=", m);
	if (!user)
	{
		m->prompt = ft_strdup("guest@minishell $ ");
		if (!m->prompt)
			m_exit("Cannot allocate memory in getprompt 1", m);
	}
	else
	{
		sufix = ft_strdup("@minishell $ ");
		if (!sufix)
			m_exit("Cannot allocate memory in getprompt 2", m);
		m->prompt = ft_strjoin(user, sufix);
		if (!m->prompt)
			m_exit("Cannot allocate memory in getprompt 3", m);
		free(user);
		free(sufix);	
	}
}
