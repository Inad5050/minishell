/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:54:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/05 17:07:29 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_tokens(char *s, t_mini *m)
{
	size_t	i;
	size_t	start;
	size_t	token_index;

	m->squote = 0;
	m->dquote = 0;
	i = 0;
	start = 0;
	token_index = 0;
	while (s[i])
	{
		while (ft_strchr(" ", s[i]) && s[i])
			i++;
		start = i;
		while ((!ft_strchr(" ", s[i]) || m->squote || m->dquote) && s[i])
		{
			m->squote = (m->squote + (!m->dquote && s[i] == '\'')) % 2;
			m->dquote = (m->dquote + (!m->squote && s[i] == '\"')) % 2;
			i++;
		}
		if (start >= ft_strlen(m->input))
			m->tokens[token_index++] = "\0";
		else
			m->tokens[token_index++] = ft_substr(s, start, i - start);
	}
}

int	ft_count_tokens(char *s, t_mini *m)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(" ", s[i]))
		{
			m->token_count++;
			while ((!ft_strchr(" ", s[i]) || m->in_quotes) && s[i])
			{
				if (!m->quote_type && (s[i] == '\"' || s[i] == '\''))
					m->quote_type = s[i];
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

int	lexer(t_mini *m)
{
	if (!ft_count_tokens(m->input, m))
		return (0);
	m->tokens = ft_calloc(m->token_count + 1, sizeof(char *));
	if (!m->tokens)
		m_exit("Cannot alocate memory in create_tokens", m);
	fill_tokens(m->input, m);
	m->tokens[m->token_count] = NULL;
	if (m->squote || m->dquote)
		return (m_err("Invalid quotes", 2, m), 0);
	return (1);
}
