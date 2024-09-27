/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:54:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/27 19:34:53 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer(t_mini *m)
{
	int	tokens_num;
	
	tokens_num = 0;
	if (!m->input)
		return (ft_printf("exit\n"), 0); //cuando el puntero del usuario es NULL terminamos la mini. Es este el comportamiento esperado?
	if (ft_strlen(m->input) > 0)
		add_history(m->input); //función del sistema relacinada con la gestión de read_line. Añade el argumento a la lista del historial de read_line. Se usa write_history para guardar el historial en el archivo seleccionado. Y read_history para leerlo.
	tokens_num = count_tokens(m);
	m->tokens = ft_calloc(tokens_num + 1, sizeof(char *));
	m->tokens[tokens_num] = NULL;
	fill_split(m);
	parser(m);
	free_lexer(m); //habria que eliminar todos los strings dentro del split, crear una funcion
	return (1);
}

int	count_tokens(t_mini *m)
{
	char	*str;
	int		i;
	int		tokens;
	
	str = m->input;
	i = 0;
	while (str[i])
	{
		while (((9 <= str[i] && str[i] <= 13) || str[i] == 32) && str[i])
			i++;
		if (problematic_chars(str[i++], m) || !str[i])
			continue;
		if (!((9 <= str[i] && str[i] <= 13) || str[i] == 32) && \
		((9 <= str[i + 1] && str[i + 1] <= 13) || (str[i + 1] == 32)))
			tokens++;
		i++;	
	}
	return (tokens);
}

void	fill_split(t_mini *m)
{
	int		i;
	int		start;
	int		token_num;
	
	i = 0;
	token_num = 0;
	while (m->input[i])
	{
		while (((9 <= m->input[i] && m->input[i] <= 13) || m->input[i] == 32) && m->input[i])
			i++;
		start = i;
		if (problematic_chars(m->input[i++], m))
			continue;
		if (!((9 <= m->input[i] && m->input[i] <= 13) || m->input[i] == 32) && \
		((9 <= m->input[i + 1] && m->input[i + 1] <= 13) || (m->input[i + 1] == 32)) && \
		!(m->in_squotes) && !(m->in_dquotes))
			m->tokens[token_num++] = ft_strndup(&(m->input[start]), i - start);
		i++;
	}
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	len;

	len = 0;
	while (src[len] && len < n)
		len++;
	dest = (char *)ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	while (len--)
		dest[len] = src[len];
	return (dest);
}
