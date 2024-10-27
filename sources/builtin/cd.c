/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:22:12 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/27 19:37:36 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *get_env_value(char **envp, char *var_name)
{
    int i;
    int len;

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

static void update_env_variable(char **envp, char *var_name, char *new_value)
{
    int i;
    int len;
    char *new_entry;

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
            return;
        }
        i++;
    }
}
int builtin_cd(t_command *cmd, t_mini *mini)
{
    char *target_dir;
    char cwd[PATH_MAX];
    char *oldpwd;

    oldpwd = getcwd(cwd, sizeof(cwd));
    target_dir = cmd->full_cmd[1] ? cmd->full_cmd[1] : get_env_value(mini->envp, "HOME");

    if (!target_dir)
    {
        ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
        return 1;
    }
    if (chdir(target_dir) == -1)
    {
        ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", target_dir);
        return 1;
    }
    update_env_variable(mini->envp, "OLDPWD", oldpwd);
    if (getcwd(cwd, sizeof(cwd)))
        update_env_variable(mini->envp, "PWD", cwd);
    return 0;
}
