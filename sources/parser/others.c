/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:15:54 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/06 17:09:14 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_user_input(t_mini *m)
{
	int	i;

	i = 0;
	if (!ft_strcmp(m->input, ""))
		return (0);
	while (m->input[i])
	{
		if (!((9 <= m->input[i] && m->input[i] <= 13) || m->input[i] == 32))
			break ;
		i++;
	}
	if (!m->input[i])
		return (0);
	return (1);
}

int	get_envp_cmd_dirs(t_mini *m)
{
	char	*dirs;

	dirs = return_envp_var("PATH=", m);
	if (!dirs)
		return (0);
	m->cmd_dirs = ft_split(dirs, ':');
	free(dirs);
	if (!m->cmd_dirs)
		m_exit("Couldn't allocate memory in get_envp_cmd_dirs", m);
	return (1);
}
