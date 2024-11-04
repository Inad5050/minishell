/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 19:58:52 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	m_err(char *str, int code, t_mini *m)
{
	free_lexer_parser(m);
	free_tcommand(m);
	g_status = code;
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	m_error_alt(char c, t_mini *m)
{
	free_lexer_parser(m);
	free_tcommand(m);
	ft_dprintf(2, "This minishell doesn't support this character: %c\n", c);
}

void	m_error_env(char *str, t_mini *m)
{
	char	*str2;

	if (!str)
	{
		m_exit("Couldn't allocate memory in m_error_env", m);
		return ;
	}
	str2 = ft_strtrim(str, "=");
	free(str);
	free_lexer_parser(m);
	free_tcommand(m);
	ft_dprintf(2, "Couldn't find %s variable\n", str2);
	free(str2);
}

void	m_exit(char *str, t_mini *m)
{
	free_lexer_parser(m);
	free_tcommand(m);
	free_tmini(m);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit (EXIT_FAILURE);
}

void	m_exit_modified(char *str, t_mini *m)
{
	free_lexer_parser(m);
	free_tcommand(m);
	free_tmini(m);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("", 2);
	exit(g_status);
}
