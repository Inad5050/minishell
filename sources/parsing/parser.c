/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:37:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/14 16:30:36 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int	expand_var(int index, t_mini *m)

int	parser(t_mini *m)
{
	int	i;

	i = 0;
	while(m->tokens[i])
		expand_var(i++, m); //epande las variables de entorno $, $? y * .
	i = 0;
	get_commands(m); //llena la lista de nodos con los comandos







}

/* 
En el contexto de un shell, "&&" y "||" son operadores lógicos:
&&: Indica que el segundo comando se debe ejecutar solo si el primero tuvo éxito (es decir, devolvió un estado de salida de 0).
||: Indica que el segundo comando se debe ejecutar solo si el primero falló (es decir, devolvió un estado de salida diferente de 0). 
*/