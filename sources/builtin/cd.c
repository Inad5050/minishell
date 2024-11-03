/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:22:12 by otboumeh          #+#    #+#             */
/*   Updated: 2024/11/03 14:07:34 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static char	*get_env_value(char **envp, char *var_name)
{
	int	i;
	int	len;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	update_env_variable(char **envp, char *var_name, char *new_value)
{
	int		i;
	int		len;
	char	*new_entry;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			new_entry = ft_strjoin(var_name, "=");
			envp[i] = ft_strjoin(new_entry, new_value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

static char *get_target_dir(t_command *cmd, t_mini *mini)
{
    if (cmd->full_cmd[1])
        return (cmd->full_cmd[1]);
    return (get_env_value(mini->envp, "HOME"));
}

static void update_pwd_variables(char *oldpwd, t_mini *mini)
{
    char cwd[PATH_MAX];
    
    update_env_variable(mini->envp, "OLDPWD", oldpwd);
    if (getcwd(cwd, sizeof(cwd)))
        update_env_variable(mini->envp, "PWD", cwd);
}

static void print_cd_error(char *dir)
{
    ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", dir);
}

int builtin_cd(t_command *cmd, t_mini *mini)
{
    char cwd[PATH_MAX];
    char *oldpwd = getcwd(cwd, sizeof(cwd));
    char *target_dir = get_target_dir(cmd, mini);

    if (!target_dir)
    {
        ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
        g_status = 1;
        return g_status;
    }
    if (chdir(target_dir) == -1)
    {
        print_cd_error(target_dir);
        g_status = 1;
        return g_status;
    }
    update_pwd_variables(oldpwd, mini);
    g_status = 0;
    return g_status;
}
