/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:53:46 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/22 16:36:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getprompt(t_mini *m)
{
	char	*user;
	char	*sufix;

	user = return_envp_variable("USER=", m);
	if (!user)
	{
		m->prompt = ft_strdup("guest@minishell $ ");
		if (!m->prompt)
			m_error("Cannot allocate memory for m->prompt", m);
	}
	else
	{
		sufix = ft_strdup("@minishell $ ");
		if (!sufix)
			m_error("Cannot allocate memory for sufix (getprompt)", m);
		m->prompt = ft_strjoin(user, sufix);
		if (!m->prompt)
			m_error("Cannot allocate memory for m->prompt", m);
		free(user);
		free(sufix);	
	}
}
