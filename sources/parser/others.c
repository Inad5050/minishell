/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:15:54 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/03 14:39:12 by dangonz3         ###   ########.fr       */
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
			break;
		i++;
	}
	if (!m->input[i])
		return (0);
	return (1);
}

int	m_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

char	*ft_strstr(char *hay, char *ndle)
{
	int	i;
	int	j;

	i = 0;
	if (!ndle)
		return (hay);
	while (hay[i])
	{
		j = 0;
		while (hay[i + j] == ndle[j] && hay[i + j])
			j++;
		if (!ndle[j])
			return (&hay[i]);
		i++;
	}
	return (NULL);	
}

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
		i++;
	if (i < n)
		n = i;
	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		ptr[i] = (char)str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}