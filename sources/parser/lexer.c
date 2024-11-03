/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:54:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/01 17:42:28 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_tokens(char *s, t_mini *m)
{
	size_t	i;
	size_t	start;
	size_t	token_index;
	
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

// m->in_quotes bolano, si estamos en comillas o no.
// m->quote_type guarda el valor ascii del tipo de comilla.
// m->token_count numero de palabras

int	ft_count_tokens(char *s, t_mini *m)
{
	int		i;

	i = 0;
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
				return (m_err("Unclosed quotes", 2, m), 0);
		}
		else
			i++;
	}
	return (1);
}

int	lexer(t_mini *m) //se necesitan más comprobaciones despues de fill_tokens? O es suficiente con if (!m->input) y if (ft_strlen(m->input) > 0)?
{
	if (!ft_count_tokens(m->input, m)) //calcula la cantidad de tokens
		return (0);
	m->tokens = ft_calloc(m->token_count + 1, sizeof(char *));
	if (!m->tokens)
		m_exit("Cannot alocate memory in create_tokens", m);
	fill_tokens(m->input, m); //llena los tokens con el contenido de m->input
	m->tokens[m->token_count] = NULL;
	if (m->squote || m->dquote) //si cualquiera de las comillas están abiertas el input es erroneo.
		return (m_err("Invalid quotes", 2, m), 0);
	return (1);
}
