/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:22:22 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/04 22:51:41 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

char	*get_env(char **envp, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(&envp[i][len + 1]));
		i++;
	}
	return (NULL);
}

int	built_pwd(int outfile)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (outfile != -1)
			dprintf(outfile, "%s\n", cwd);
		g_status = 0;
	}
	else
	{
		perror("pwd");
		g_status = 1;
	}
	return (g_status);
}
