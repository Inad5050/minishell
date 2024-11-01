/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:33:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/01 20:50:50 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_var(int index, t_mini *m)
{
	char	*tkn;
	
	tkn = m->tokens[index];
	if (ft_strstr(tkn, "$?")) //$? es el signo que indica que se debe mostrar el estado de salida del último comando ejecutado.
			return (m->tokens[index] = ft_itoa(g_status), 1);
	if (ft_strchr(tkn, '$') && ft_strlen(tkn) > 1)  //es el signo de una variable local que debe ser expandida. No se expanden en comillas simples \'.
	{
		if (!get_var_name_expand(tkn, index, m))
			return (0);
	}
	return (1);
}


/* char *strndup(const char *s, size_t n) 
{
    size_t len = ft_strnlen(s, n); // Asegura que no copiemos más de `n` caracteres
    char *nuevo = malloc(len + 1); // Asigna espacio para `len` caracteres + `\0`
    
    if (nuevo) {
        strncpy(nuevo, s, len);
        nuevo[len] = '\0'; // Añade el terminador nulo
    }
    return nuevo;
} */


int	get_var_name_expand(char *tkn, int index, t_mini *m) //consigue el nombre de la variable a expandir de tkn y se la pasa a return_envp_variable
{
	char	*pre_var_name;
	char	*pre_pre_var_name;
	int		i;
	char	*var_name;
	char	*var_name_alt;
	char	*variable;
	char	*variable_alt;
	/* char	*str; */
	
	index++;
	
	pre_var_name = ft_strstr(tkn, "$");
	i = 0;
	while (pre_var_name[i])
	{
		if (pre_var_name[i] == '\0' || (9 <= pre_var_name[i] && pre_var_name[i] <= 13) || pre_var_name[i] == 32 || pre_var_name[i] == 34)
			break;
		i++;
	}

	ft_printf("pre_var_name = %s\n", pre_var_name);

	pre_pre_var_name = ft_strndup(pre_var_name, i);
	if (!pre_pre_var_name)
		return (m_exit("Couldn't alloc in get_var_name_expand", m), 0);

	ft_printf("pre_pre_var_name = %s\n", pre_pre_var_name);
	
	var_name = ft_strtrim(pre_pre_var_name, "$");

	ft_printf("var_name = %s\n", var_name);
	
	var_name_alt = ft_strjoin(var_name, "=");
	if (!var_name_alt)
		return (free(var_name), free(var_name_alt), \
		m_exit("Couldn't alloc in get_var_name_expand", m), 0);

	ft_printf("var_name_alt = %s\n", var_name_alt);
	
	variable = return_envp_var(var_name, m);
	if (!variable)
		return (free(var_name), free(var_name_alt), free(variable), \
		m_err("Couldn't find env variable\n", 2, m), 0);
	
	ft_printf("variable = %s\n", variable);
	
	variable_alt = ft_strtrim(variable, "=");
	if (!variable_alt)
		return (free(var_name), free(var_name_alt), free(variable), \
		free(variable_alt), m_exit("Couldn't alloc in get_var_name_expand", m), 0);

	ft_printf("variable_alt = %s\n", variable_alt);

	change_token_with_expansion(tkn, variable_alt, pre_pre_var_name, m);
		
/* 	str = get_expanded_str(variable_alt, var_name, tkn, m);

	free(var_name);
	free(var_name_alt);
	free(variable);
	free(variable_alt);
	free(str); */
	
/* 	free(variable);
	free(var_name);
	free(m->tokens[index]);
	m->tokens[index] = str; */
	return (1);
}

int	change_token_with_expansion(char *tkn, char *variable_alt, char *pre_pre_var_name, t_mini *m)
{
	char	*tkn_var_located;
	char	**tkn_split;
	/* int		lenght_split; */
	int		i;
	char	*tmp;
	char	*tkn_split_reformed;
	char	*tkn_split_with_space;
	int		tkn_pre_var_name_index;
	char	*tkn_pre_var_name;
	char	*tkn_pre_var_name_definitive;
	char	*definitivo;

	/* lenght_split = 0; */
	
	i = m->cmd_count;

	tkn_var_located = ft_strstr(tkn, pre_pre_var_name);

	ft_printf("tkn_var_located = %s\n", tkn_var_located);
	
	tkn_split = ft_split(tkn_var_located, ' ');

	i = 0;
	while (tkn_split[i])
	{
		ft_printf("tkn_split[%i] = %s\n", i, tkn_split[i]);
		i++;
	}
	variable_alt++;

	i = 0;
	while (tkn_split[i])
	{
		if (!ft_strcmp(tkn_split[i], pre_pre_var_name))
			break;
		i++;
	}

	tkn_pre_var_name = ft_strstr(tkn, pre_pre_var_name);
	tkn_pre_var_name_index = (int)(tkn_pre_var_name - tkn);
	tkn_pre_var_name_definitive = ft_strndup(tkn, tkn_pre_var_name_index);
	if (!tkn_pre_var_name_definitive)
		return (m_exit("Couldn't alloc in change_token_with_expansion", m), 0);
	
	ft_printf("OLA tkn_pre_var_name_definitive = %s\n", tkn_pre_var_name_definitive);

	
	tmp = tkn_split[i];
	tkn_split[i] = variable_alt;
	free(tmp);

	i = 0;
	tkn_split_reformed = ft_strdup("");
	if (!tkn_split_reformed)
		return (m_exit("Couldn't alloc in change_token_with_expansion", m), 0);
	
	if (tkn_split[i + 1])
	{
		while (tkn_split[i])
		{
			tmp = tkn_split_reformed;
			if (tkn_split[i + 1])
			{
				tkn_split_with_space = ft_strjoin(tkn_split[i], " ");
				if (!tkn_split_with_space)
					return (m_exit("Couldn't alloc in change_token_with_expansion", m), 0);
			}
			else
				tkn_split_with_space = tkn_split[i];
			tkn_split_reformed = ft_strjoin(tkn_split_reformed, tkn_split_with_space);
			if (!tkn_split_reformed)
				return (m_exit("Couldn't alloc in change_token_with_expansion", m), 0);
			free(tmp);
			i++;
		}
	}
	
	i = 0;

	
	ft_printf("tkn_split_reformed = %s\n", tkn_split_reformed);
	
	
	definitivo = ft_strjoin(tkn_pre_var_name_definitive, tkn_split_reformed);
	if (!tkn_pre_var_name_definitive)
		return (m_exit("Couldn't alloc in change_token_with_expansion", m), 0);
	
	
	ft_printf("definitivo = %s\n", definitivo);



	return (1);
}

/* char	*get_expanded_str(char *variable, char *var_name, char *tkn, t_mini *m) //crea un string nueva que copia tkn y sustituye $VAR_NAME por la variable
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	index;

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
} */
