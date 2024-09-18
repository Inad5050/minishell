/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:35:33 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/18 17:31:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_exit(char	*str)
{
	//libera la memoria de las estrcuturas. Según esta lógica toda la memoria dinámica debería ser liberada al momento o debería ser parte de la estructura
	//destrucción de semaforos/mutex
	ft_putstr_fd("str\n", 2); //imprime el mensaje de error en la STDERR
	exit(g_status); //terminamos el programa con el código de error adecuado. = 0 si no hay errores. (g_status) es la avriable global
}

