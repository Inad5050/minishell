/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:37:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/03 14:17:37 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_mini *m)
{
	int	i;

	i = 0;
	while(m->tokens[i])
	{
		if (!expand_var(i, m)) //epande las variables de entorno "$" y "$?""
			return (0);
		i++;
	}
	if (!token_check(m))
		return (0);
	if (!t_commands(m)) //llena las estructuras t_command con sus valores correspondientes.
		return (0);
	if (!open_files(m)) //intenta abrir o crear los archivos de las redirecciones + here_doc
		return (0);
	if (!pre_check_commands(m))
		return (0);
	if (!check_commands(m)) //comprueba si el comando existe y si es built_in
		return (0);
/* 	if (!check_path_env(m))
		return (0); */
	if (!delete_quotes(m))
		return (0);
	return (1);
}
