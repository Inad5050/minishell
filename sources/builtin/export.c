/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:55:19 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/29 10:21:34 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int update_env_var(char **envp, const char *arg, char *new_var, int len)
{
    int i = 0;

    while (envp[i])
    {
        if (strncmp(envp[i], arg, len) == 0 && envp[i][len] == '=')
        {
            free(envp[i]);
            envp[i] = new_var;
            return (0);
        }
        i++;
    }
    return (1);
}

int add_new_env_var(t_mini *mini, char *new_var)
{
    int i = 0;
    char **new_envp;

    while (mini->envp && mini->envp[i])
        i++;
    new_envp = realloc(mini->envp, (i + 2) * sizeof(char *));
    if (!new_envp)
    {
        free(new_var);
        return (1);
    }
    mini->envp = new_envp;
    mini->envp[i] = new_var;
    mini->envp[i + 1] = NULL;
    return (0);
}

int add_or_update_env(const char *arg, t_mini *mini)
{
    char *equal_sign = strchr(arg, '=');
    char *new_var;

    if (!equal_sign)
        return (0);
    new_var = strdup(arg);
    if (!new_var)
        return (1);
    if (update_env_var(mini->envp, arg, new_var, equal_sign - arg) == 0)
        return (0);
    return (add_new_env_var(mini, new_var));
}

int export_var(const char *arg, int outfile, t_mini *mini)
{
    int i = 0;

    if (arg == NULL)
    {
        while (mini->envp && mini->envp[i])
        {
            dprintf(outfile, "declare -x %s\n", mini->envp[i]);
            i++;
        }
        g_status = 0;
    }
    else if (add_or_update_env(arg, mini) == 0)
        g_status = 0;
    else
        g_status = 1;
    return (g_status);
}