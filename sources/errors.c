/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/20 16:34:50 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_error(char	*str, t_mini *m) //imprime un mensaje de error, pero no cierra la minishell. Probablemente lo uses tu Otman. No se si deberia hacer algo más que imprimir el error.
{
	ft_putstr_fd(str, 2); //imprime el mensaje de error en la STDERR
	ft_putstr_fd("\n", 2); //imprime el mensaje de error en la STDERR
}
