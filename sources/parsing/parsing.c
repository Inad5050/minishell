/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:54:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/22 15:24:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*check_args(t_mini *m)
{
	if (!m->input)
		return (m_exit("no arguments"), NULL); //cuando el input del usuario es NULL terminamos la mini. Es este el comportamiento esperado?
	if (m->input[0] == '\0')
		add_history(m->input); //función del sistema relacinada con la gestión de read_line. Añade el argumento a la lista del historial de read_line. Se usa write_history para guardar el historial en el archivo seleccionad. Y read_history para leerlo.
	m->split = ft_cmdtrim(m->input, " "); //se encarga de dividir la cadena de entrada en un array de palabras usando el delimitador del segundo argumento. Es como el split, pero tiene que tener en cuenta el uso de las comillas simples y dobles.
	(!m->split)
		m_exit("mensaje de error");
	parse_args(m);
		
}

void	parse_args(t_mini *m)
{
	p->cmds = fill_nodes(m);
			
}

void	fill_nodes(m) //carga los nodos de las estructuras con la informacion del parseo. convierte un array de argumentos procesados en una lista enlazada de nodos de comando. Cada nodo de la lista representa un comando y sus parámetros. La función maneja delimitadores como | para separar los comandos y se asegura de construir la lista de manera adecuada, manejando errores y liberando memoria al final.
{
		
}
