/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:33:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/03 16:35:19 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_var(int index, t_mini *m)
{
	char	*tmp;

	if (m->tokens[index][0] == '\'' && m->tokens[index][ft_strlen(m->tokens[index]) - 1] == '\'')
		return (1);
	if (ft_strstr(m->tokens[index], "$?")) //$? es el signo que indica que se debe mostrar el estado de salida del último comando ejecutado.
			return (m->tokens[index] = ft_itoa(g_status), 1);
	if (ft_strchr(m->tokens[index], '$') && ft_strlen(m->tokens[index]) > 1)  //es el signo de una variable local que debe ser expandida. No se expanden en comillas simples \'.
	{				
		if (!exchange_token_expansion(m->tokens[index], m))
			return (0);
		tmp = m->tokens[index];
		m->tokens[index] = ft_strdup(m->new_tkn);
		if (!m->tokens[index])
			return (m_exit("Couldn't alloc in expand_var", m), 0);
		free(tmp);		
	}
	return (1);
}

int	exchange_token_expansion(char *tkn, t_mini *m) //consigue el nombre de la variable a expandir de tkn y se la pasa a return_envp_variable
{
	int		i;
		
	i = 0;
	m->str_var_name = ft_strstr(tkn, "$");
	while (m->str_var_name[i])
	{
		if (m->str_var_name[i] == '\0' || (9 <= m->str_var_name[i] && m->str_var_name[i] <= 13) || \
		m->str_var_name[i] == 32 || m->str_var_name[i] == 34)
			break;
		i++;
	}
	m->var_name_with_dollar = ft_strndup(m->str_var_name, i);
	if (!m->var_name_with_dollar)
		return (m_exit("Couldn't alloc in exchange_token_expansion", m), 0);
	m->var_name = ft_strtrim(m->var_name_with_dollar, "$");
	m->var_name_envp = ft_strjoin(m->var_name, "=");
	if (!m->var_name_envp)
		return (m_exit("Couldn't alloc in exchange_token_expansion", m), 0);
	if (!exchange_token_expansion_aux(tkn, m))
		return (0);
	return (1);
}

int	exchange_token_expansion_aux(char *tkn, t_mini *m)
{
	m->variable_envp = return_envp_var(m->var_name, m);
	if (!m->variable_envp)
		return (0);
	m->variable = ft_strtrim(m->variable_envp, "=");
	if (!m->variable)
		return (m_exit("Couldn't alloc in exchange_token_expansion_aux", m), 0);
	if (!exchange_token_expansion_aux_aux(tkn, m))
		return (0);
	return (1);
}

int	exchange_token_expansion_aux_aux(char *tkn, t_mini *m)
{
	int		var_name_size;
	
	var_name_size = 0;
	m->var_name_ptr = ft_strstr(tkn, m->var_name_with_dollar);
	m->str_pre_var_name = ft_strndup(tkn, (int)(m->var_name_ptr - tkn));
	if (!m->str_pre_var_name)
		return (m_exit("Couldn't alloc in exchange_token_expansion_aux_aux", m), 0);
	var_name_size = ft_strlen(m->var_name_with_dollar);
	m->str_post_var_name = ft_strdup(m->var_name_ptr + var_name_size);
	if (!m->str_post_var_name)
		return (m_exit("Couldn't alloc in exchange_token_expansion_aux_aux", m), 0);
	m->str_pre_plus_var = ft_strjoin(m->str_pre_var_name, m->variable);
	if (!m->str_pre_plus_var)
		return (m_exit("Couldn't alloc in exchange_token_expansion_aux_aux", m), 0);
	m->new_tkn = ft_strjoin(m->str_pre_plus_var, m->str_post_var_name);
	if (!m->new_tkn)
		return (m_exit("Couldn't alloc in exchange_token_expansion_aux_aux", m), 0);
	return (1);
}
