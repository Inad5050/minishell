/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:33:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/16 18:54:57 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_expanded_str(char *variable, char *var_name, char *tkn, t_mini *m) //crea un string nueva que copia tkn y sustituye $VAR_NAME por la variable
{
	char	*str;
	int		i;
	int		j;
	int		index;

	i = 0;
	while (tkn[i] != '$' && tkn[i])
		i++;
	j = 0;
	while (tkn[i + j + ft_strlen(var_name)])
		j++;
	str = ft_calloc(i + j + ft_strlen(variable) + 1, sizeof(char));
	if (!str)
		m_exit("Cannot assign memory in expand_env_var", m);
	index = -1;
	while (++index < i)
		str[index] = tkn[index];
	while (++index < i + ft_strlen(variable))
		str[index] = variable[index - i];
	while (++index < i + ft_strlen(variable) + j)
		str[index] = tkn[i + index + ft_strlen(variable)];
	str[++index] = '\0';
	return (str);
}

void	get_env_var(char *tkn, int index, t_mini *m) //consigue el nombre de la variable a expandir de tkn y se la pasa a return_envp_variable
{
	int		i;
	int		j;
	char	*var_name;
	char	*variable;
	char	*str;
	
	i = 0;
	while (tkn[i++] != '$' && tkn[i])
		i++;
	j = 0;
	while (ft_isalpha(tkn[i + j]) && tkn[i + j])
		j++;
	var_name = ft_calloc(j + 1, sizeof(char));
	if (!var_name)
		m_exit(var_name, m);
	variable = return_envp_var(var_name, m);
	str = get_expanded_str(variable, var_name, tkn, m);
	free(variable);
	free(var_name);
	free(m->tokens[index]);
	m->tokens[index] = str;
}

int	expand_var(int index, t_mini *m)
{
	char	*tkn;
	int		i;
	char	*str;
	
	m->tokens[index] = tkn;
	i = 0;
	if (ft_strchr(tkn, '$') && tkn[0] != '\'' && ft_strlen(tkn) > 1)  //es el signo de una variable local que debe ser expandida. No se expanden en comillas simples \'.
	{
		if (ft_strstr(tkn, "$?")) //$? es el signo que indica que se debe mostrar el estado de salida del último comando ejecutado.
			return (get_err_code(m), 1); //POR_HACER
		return (get_env_var(tkn, index, m), 1);
	}
}

