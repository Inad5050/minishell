/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:37:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/09 16:58:56 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	parser(t_mini *m)
{
	int	i;

	i = 0;
	while (m->tokens[i])
		if (expand_var(i, m) == 2) //gestiona el caso "*\0". En este caso la tokens[i] tiene que expandirse de char * a char **.
	
}

/* 
En el contexto de un shell, "&&" y "||" son operadores lógicos:
&&: Indica que el segundo comando se debe ejecutar solo si el primero tuvo éxito (es decir, devolvió un estado de salida de 0).
||: Indica que el segundo comando se debe ejecutar solo si el primero falló (es decir, devolvió un estado de salida diferente de 0). 
*/