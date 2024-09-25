/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:06:40 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/22 20:07:02 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i += in_squotes(c, m);
	i += escaped(c, m);
	i += in_dquotes(c, m);
	return (i);
}

int	in_squotes(char	c, t_mini *m)
{
	if (c == '\'')
		return (m->in_squotes = !m->in_squotes, 1);
	else
		return (0);
}

int	in_dquotes(char	c, t_mini *m)
{
	if (c == '"')
		return (m->in_dquotes = !m->in_dquotes, 1);
	else
		return (0);
}

int	escaped(char	c, t_mini *m)
{
	if (c == '\\' && !(m->escaped))
		return (m->escaped = true, 1);
	else
		return (0);	
}