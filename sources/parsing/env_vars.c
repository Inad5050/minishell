/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:33:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/27 21:19:28 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_variable(char *lex_tok, char *var)
{
	char	*env_var;
	char	*var_value;
	int		i;

	var_value = get_env_var_value(get_envv(), var);
	free(var);
	if (var_value == NULL)
		return (NULL);
	env_var = ft_calloc(ft_strlen(lex_tok) + ft_strlen(var_value) + 1, 1);
	if (env_var == NULL)
		return (NULL);
	i = -1;
	while (lex_tok[++i] && lex_tok[i] != '$')
		env_var[i] = lex_tok[i];
	env_var = ft_append(&env_var, var_value);
	if (env_var == NULL)
		return (var_value);
	while ((lex_tok[i] == '$') || (lex_tok[i] && ft_isalpha(lex_tok[i])))
		i++;
	env_var = ft_append(&env_var, lex_tok + i);
	if (env_var == NULL)
		return (NULL);
	free(var_value);
	return (env_var);
}

static char	*get_var(char *lex_tok)
{
	char	*var;
	char	*lex_buf;
	int		i;

	lex_buf = lex_tok;
	var = ft_calloc(ft_strlen(lex_buf) + 1, sizeof(*var));
	if (var == NULL)
		return (NULL);
	lex_buf = ft_strchr(lex_buf, '$') + 1;
	i = 0;
	while (lex_buf && *lex_buf && ft_isalpha(*lex_buf))
		var[i++] = *lex_buf++;
	return (var);
}

/**
 * @brief  Interprets enviroment variables of current lexer token
 * @note   Frees current lex_tok if necessary
 * @param  *lex_tok: Current lexer token
 * @retval Returns interpreted lexer token
 */
char	*interprete_env_var(char *lex_tok)
{
	char	*interpreted_token;

	interpreted_token = lex_tok;
	if (lex_tok[0] != '\'' && ft_strlen(lex_tok) > 1 \
	&& ft_strchr(lex_tok, '$'))
	{
		if (ft_strstr(lex_tok, "$?"))
		{
			free(lex_tok);
			return (ft_itoa(get_err_code()));
		}
		interpreted_token = get_env_variable(lex_tok, get_var(lex_tok));
		free(lex_tok);
		return (interpreted_token);
	}
	if (!ft_strchr(lex_tok, '\'') && !ft_strchr(lex_tok, '\"') \
	&& ft_strcmp(lex_tok, "*\0") == 0)
	{
		free(lex_tok);
		return (get_dir_items());
	}
	return (interpreted_token);
}

int	expand_env_variable(int	index, t_mini *m)
{
	char	*token;

	token = m->tokens[index];
	if (!ft_strchr(token, '$') || *token == '\'') //las variables de entorn se identifican con el simbolo '$', y deben ser expandidas en comillas compuestas "", pero no en comillas simples ''
		return (0);
	if (ft_strcmp(token, "*\0")) //el asterisco (*) es un carácter especial que se usa en el "globbing". El globbing permite a los usuarios hacer coincidir múltiples archivos en un directorio sin tener que enumerar todos los nombres de archivo explícitamente. Por ejemplo, si un directorio contiene archivos como file1.txt, file2.txt, y document.pdf, el uso de * en un comando puede expandirse a todos esos archivos.
		globbing(); //POR HACER
	if (ft_strlen(token) > 0)
	{
		if (ft_strstr(token, "$?")) //la variable '$?' se utiliza para obtener el código de salida del último comando ejecutado. Este código es un valor entero que indica el estado de finalización del último proceso. 0 suele indicar que se ejecuto correctamente. Cualquier otro número (generalmente entre 1 y 255) indica un error o una condición específica de fallo. 
			return (get_err_code(), 0);
		
	
		
	}







	
}
