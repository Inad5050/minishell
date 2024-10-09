/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:54:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/09 21:13:48 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
} */

void	fill_tokens(char *s, t_mini *m)
{
	int		i;
	int		start;
	int		token_index;
	
	m->squote = 0; // Bandera para ver si estamos dentro de comillas o no.
	m->dquote = 0; // Almacena el valor ascii del tipo de comilla.
	i = 0;
	start = 0;
	token_index = 0;
	while (s[i])
	{
		while (ft_strchr(" ", s[i]) && s[i]) //avanza hasta encontrar el primer caracter no delimitador, en este caso solo tiene en cuenta los espacios
			i++;
		start = i;
		while ((!ft_strchr(" ", s[i]) || m->squote || m->dquote) && s[i]) //mientras no haya espacios o estemos entre comillas
		{
			m->squote = (m->squote + (!m->dquote && s[i] == '\'')) % 2; //entramos o salimos de cada tipo de comilla comprobando que no estemos en el otro tipo de comilla
			m->dquote = (m->dquote + (!m->squote && s[i] == '\"')) % 2;
			i++;
		}
		if (start >= ft_strlen(m->input))
			m->tokens[token_index++] = "\0";
		else
			m->tokens[token_index++] = ft_substr(s, start, i - start);
	}
}

void	ft_count_tokens(char *s, t_mini *m)
{
	int		i;

	i = 0;
	m->in_quotes = 0; //bolano, si estamos en comillas o no.
	m->quote_type = 0; //guarda el valor ascii del tipo de comilla.
	m->token_count = 0; //numero de palabras
	while (s[i])
	{
		if (!ft_strchr(" ", s[i])) //comprobamos si el caracter actual es un delimitador " ".
		{
			m->token_count++;
			while ((!ft_strchr(" ", s[i]) || m->in_quotes) && s[i]) //si el caracter no es un delimitador o si estamos en comillas entra en el bucle
			{
				if (!m->quote_type && (s[i] == '\"' || s[i] == '\'')) //si no estamos en comillas y el caracter es una comilla
					m->quote_type = s[i];  //m->quote_type se convierte en e
				m->in_quotes = (m->in_quotes + (s[i] == m->quote_type)) % 2;
				m->quote_type *= m->in_quotes != 0;
				i++;
			}
			if (m->in_quotes)
				return (m_error("Unclosed quotes", m), -1);
		}
		else
			i++;
	}
}

int	lexer(t_mini *m)
{
	if (!m->input)
		return (ft_printf("exit\n"), 0); //cuando el puntero del usuario es NULL terminamos la mini. Es este el comportamiento esperado?
	if (ft_strlen(m->input) > 0)
		add_history(m->input); //función del sistema relacinada con la gestión de read_line. Añade el argumento a la lista del historial de read_line. Se usa write_history para guardar el historial en el archivo seleccionado. Y read_history para leerlo.
	ft_count_tokens(m->input, m); //calcula la cantidad de tokens
	m->tokens = ft_calloc(m->token_count + 1, sizeof(char *));
	if (!m->tokens)
		m_exit("Cannot alocate memory in create_tokens", m);
	fill_tokens(m->input, m); //llena los tokens con el contenido de m->input
	m->tokens[m->token_count] = NULL;	
	parser(m);
}
