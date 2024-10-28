/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:55:19 by otboumeh          #+#    #+#             */
/*   Updated: 2024/10/27 19:45:02 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int find_env_var(char *var, t_mini *mini)
{
    int i = 0;
    size_t len = ft_strlen(var);
    
    while (mini->envp[i])
    {
        if (ft_strncmp(mini->envp[i], var, len) == 0 && mini->envp[i][len] == '=')
            return i;
        i++;
    }
    return -1;
}

static void update_env_var(int var_idx, char *new_var, t_mini *mini)
{
    free(mini->envp[var_idx]);
    mini->envp[var_idx] = new_var;
}

static char **create_new_env_array(t_mini *mini, char *new_var)
{
    int i = 0;
    while (mini->envp[i])
        i++;

    char **new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
        return NULL;

    for (int j = 0; j < i; j++)
        new_envp[j] = mini->envp[j];

    new_envp[i] = new_var;
    new_envp[i + 1] = NULL;
    return new_envp;
}

static int set_env_var(char *var_value, t_mini *mini)
{
    char *new_var = ft_strdup(var_value);
    if (!new_var)
        return(m_error("Memory allocation failed", mini),0);
    int var_idx = find_env_var(var_value, mini);
    if (var_idx >= 0)
        update_env_var(var_idx, new_var, mini);
    else
    {
        char **new_envp = create_new_env_array(mini, new_var);
        if (!new_envp)
        {
            free(new_var);
            return(m_error("Memory allocation failed", mini),0);
        }
        free(mini->envp);
        mini->envp = new_envp;
    }
}

int export_var(char *var, int outfile, t_mini *mini)
{
    if (var == NULL)
    {
        for (int i = 0; mini->envp[i] != NULL; i++)
        {
            dprintf(outfile, "%s\n", mini->envp[i]);
        }
        g_status = 0;
        return g_status;
    }  
    if (ft_strchr(var, '=') == NULL)
    {
        ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", var);
        g_status = 1;
        return g_status;
    }   
    char *name = ft_strndup(var, ft_strchr(var, '=') - var);
    char *value = ft_strdup(ft_strchr(var, '=') + 1); 
    update_env_variable(mini->envp, name, value); 
    free(name);
    free(value);  
    g_status = 0; 
    return (g_status);
}
