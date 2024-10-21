/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/18 18:32:43 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_error(char *str, t_mini *m) //imprime un mensaje de error, pero no cierra la minishell. Libera la memoria asociada con el parseo y la ejecución.
{
	free_lexer_parser(m);
	free_tcommand(m);

	FREE_EXECUTION();
	
	ft_putstr_fd(str, 2); //imprime el mensaje de error en la STDERR
	ft_putstr_fd("\n", 2); //imprime el mensaje de error en la STDERR
}

void	m_exit(char *str, t_mini *m) //imprime un mensaje de error, pero no cierra la minishell. Libera la memoria asociada con el parseo y la ejecución.
{
	free_lexer_parser(m);
	free_tcommand(m);

	FREE_EXECUTION();
	
	free_tmini(m);
	ft_putstr_fd(str, 2); //imprime el mensaje de error en la STDERR
	ft_putstr_fd("\n", 2); //imprime el mensaje de error en la STDERR
	exit;
}
