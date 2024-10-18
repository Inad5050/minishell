/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:37:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/18 16:26:58 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int	expand_var(int index, t_mini *m)

int	parser(t_mini *m)
{
	int	i;

	i = 0;
	while(m->tokens[i])
		expand_var(i++, m); //epande las variables de entorno "$" y "$?""
	i = 0;
	token_assign(m); //llena las estructuras t_command con sus valores correspondientes.
	open_files(m); //intenta abrir o crear los archivos de las redirecciones + here_doc
	check_commands(m); //comprueba si el comando existe y si es built_in
	get_path(m); //si la funcion NO es built_in, consigue el path a la funcion y lo copia en full_path dentro de la estructura t_command que corresponda
	free_lexer_parser(m); //libera toda la memoria asociada con el lexer y el parser.

	EXECUTE(m); //Otman hace sus cosas;	
}

/* 
En el contexto de un shell, "&&" y "||" son operadores lógicos:
&&: Indica que el segundo comando se debe ejecutar solo si el primero tuvo éxito (es decir, devolvió un estado de salida de 0).
||: Indica que el segundo comando se debe ejecutar solo si el primero falló (es decir, devolvió un estado de salida diferente de 0). 
*/
