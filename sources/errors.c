/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/29 23:33:05 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	m_error(char *str, t_mini *m) //imprime un mensaje de error, pero no cierra la minishell. Libera la memoria asociada con el parseo y la ejecución.
{
	free_lexer_parser(m);
	free_tcommand(m);
	ft_putstr_fd(str, 2); //imprime el mensaje de error en la STDERR
	ft_putstr_fd("\n", 2); //imprime el mensaje de error en la STDERR
}

void	m_error_alt(char c, t_mini *m)
{
	free_lexer_parser(m);
	free_tcommand(m);
	ft_dprintf(2, "This minishell doesn't support this character: %c\n", c);
}

void	m_exit(char *str, t_mini *m) //imprime un mensaje de error, pero no cierra la minishell. Libera la memoria asociada con el parseo y la ejecución.
{
	free_lexer_parser(m);
	free_tcommand(m);
	free_tmini(m);
	ft_putstr_fd(str, 2); //imprime el mensaje de error en la STDERR
	ft_putstr_fd("\n", 2); //imprime el mensaje de error en la STDERR
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