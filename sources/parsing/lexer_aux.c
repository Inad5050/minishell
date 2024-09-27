/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:06:40 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/27 19:35:17 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	problematic_chars(char	c, t_mini *m)
{
	int	i;

	i = 0;
	if (m->in_squotes)
		i = in_squotes(c, m);
	else if (m->escaped)
		i = escaped(c, m);
	else if (m->in_dquotes)
		i = in_dquotes(c, m);
	else
		i = in_squotes(c, m) || escaped(c, m) || in_dquotes(c, m); //deja de ejecutar las funciones en el momento en el que una de ellas devuelve un valor positivo
	return (i);
}

int	in_squotes(char	c, t_mini *m) //las comillas simples invalidan todo, hasta que no salgamos de las comillas ningun caracter tiene significancia
{
	if (c == '\'')
		return (m->in_squotes = !m->in_squotes, 1);
	else
		return (0);
}

int	escaped(char c, t_mini *m)
{
	if (c == '\\' && !(m->escaped))
		return (m->escaped = true, 1);
	else
		return (0);	
}

int	in_dquotes(char	c, t_mini *m) //las comillas dobles no invalidan los backslash
{
	if (c == '"')
		return (m->in_dquotes = !m->in_dquotes, 1);
	else
		return (0);
}

void	free_lexer(t_mini *m) //liberamos la memoria de todo el proceso intermedio entre recibir el input del usaurio y cargar la estructura t_command
{
	int	i;
	
	i = 0;
	if (m->input)
		free(m->input);
	if (m->tokens)
	{
		while (m->tokens[i])
			free(m->tokens[i++]);
	}
	free(m->tokens);
	m->in_squotes = 0;
	m->in_dquotes = 0;
	m->escaped = 0;
}
