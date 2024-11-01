/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:37:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/01 13:54:08 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int	expand_var(int index, t_mini *m)

int	parser(t_mini *m)
{
	int	i;

	i = 0;
	while(m->tokens[i])
	{
		if (!expand_var(i++, m)) //epande las variables de entorno "$" y "$?""
			return (0);
	}
	if (!token_check(m))
		return (0);
	if (!t_commands(m)) //llena las estructuras t_command con sus valores correspondientes.
		return (0);
	if (!open_files(m)) //intenta abrir o crear los archivos de las redirecciones + here_doc
		return (0);
	if (!check_commands(m)) //comprueba si el comando existe y si es built_in
		return (0);
	printf("check_commands Dirección de full_cmd[0]: %p\n", (void *)m->cmds[0].full_cmd[0]);
	printf("check_commands Dirección de full_path: %p\n", (void *)m->cmds[0].full_path);
	return (1);
}

/* 
En el contexto de un shell, "&&" y "||" son operadores lógicos:
&&: Indica que el segundo comando se debe ejecutar solo si el primero tuvo éxito (es decir, devolvió un estado de salida de 0).
||: Indica que el segundo comando se debe ejecutar solo si el primero falló (es decir, devolvió un estado de salida diferente de 0). 
*/

int	m_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}