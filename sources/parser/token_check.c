/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:20:56 by dani              #+#    #+#             */
/*   Updated: 2024/11/01 17:40:19 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_check(t_mini *m)
{
	if (!check_problem_chars(m))
		return (0);
	if (!check_pipes(m))
		return (m_err("Incorrect pipes", 2, m), 0);
	if (!check_redirections(m))
		return (m_err("Incorrect redirections", 2, m), 0);
	return (1);
}

int	check_problem_chars(t_mini *m)
{
	int	i;
	int	x;
	int	dquote;
	int	squote;
	
	dquote = 0;
	squote = 0;
	i = 0;
	while (m->tokens[i])
	{
		x = 0;
		while (m->tokens[i][x])
		{
			if (m->tokens[i][x] == 34)
				dquote = (dquote + 1) % 2;
			if (m->tokens[i][x] == 39)
				squote = (squote + 1) % 2;
			if (!check_problem_chars_aux(m->tokens[i][x], dquote, squote, m))
				return (0);
			x++;
		}	
		i++;
	}
	return (1);	
}

int	check_problem_chars_aux(char tkn, int dquote, int squote, t_mini *m)
{
	if (squote)
		return (1);
	if (dquote)
	{
		if (tkn != '`' && tkn != '\\')
			return (1);
	}
	if (tkn == '`' && tkn == '\\' && tkn == '*' && tkn == '{' && tkn == '}' && \
	tkn == '[' && tkn == ']' && tkn == '(' && tkn == ')' && tkn == ';')
		return (m_error_alt(tkn, m), 0);
	return (1);
}

int	check_pipes(t_mini *m)
{
	int	i;
	int	previous_pipe;

	previous_pipe = 0;
	i = -1;
	while (m->tokens[++i])
	{
		if (!ft_strcmp(m->tokens[i], "|"))
		{
			if (previous_pipe) //dos pipes seguidas
				return (0);
			if (i == 0 || i == m_strlen(m->tokens)) //primer o último token es un pipe
				return (0);
			previous_pipe = 1;
		}
		else
			previous_pipe = 0;
	}
	return (1);
}

int	check_redirections(t_mini *m)
{
	int	i;
	int	previous_re;

	previous_re = 0;
	i = 0;
	while (m->tokens[i])
	{
		if (!ft_strcmp(m->tokens[i], "<") || !ft_strcmp(m->tokens[i], ">") || \
		!ft_strcmp(m->tokens[i], ">>"))
		{
			if (previous_re) //dos redirecciones seguidas
				return (0);
			if (i == 0 || i == m_strlen(m->tokens)) //primer o último token es una redireccion
				return (0);
			previous_re = 1;
		}
		else
			previous_re = 0;
		i++;		
	}
	return (1);
}
