/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:29:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/16 18:48:08 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	identify_token_alt(char *tkn, int code, int cmd_index, t_mini *m) //Su objetivo es contar el tamaño que deberia tener el full_cmd de cada t_command. Distingue entre cuatro tipos de tokens, el grupo 0 (comando, argumentos y opciones) va en la estructura full_cmd de t_command, el grupo 1 son los '|' que indican que debemos empezar a rellenar el full_cmd de una nueva estructura t_command, el 2 grupo son las redirecciones, el 3 grupo son los argumentos de las redirecciones
{
	if (code == 2) //el anterior token era una redireccion y este debe sser su argumento.
		return (3);	
	else if (tkn == "<" || tkn == "<<" || tkn == ">" || tkn == ">>")
		return (2);
	else if (tkn == "|")
		return (1);
	return (0)
}

void	initiate_command_structs(t_mini *m) //su objetivo es alojar memoria para cada m->cmds[].full_cmd.
{
	int	i;
	int	cmd_index;
	int code;
	int	size;

	i = 0;
	cmd_index = 0;
	while (m->tokens[i] && cmd_index < m->cmd_count)
	{
		code = identify_token_alt(m->tokens[i], 0, cmd_index, m);
		if (code == 0)
			size++;	
		if (code == 2) //si hemos encontrado un pipe
		{
			m->cmds[cmd_index].full_cmd = ft_calloc(size + 1, sizeof(char *));
			cmd_index++;
			size = 0;
		}
		i++;
	}
}

void	initiate_get_commands(t_mini *m) //consigue los valores de m->path y m->cmd_dirs. Aloja meoria para m->cmds.
{
	int	i;
	int	x;
	
	m->path = return_envp_var("PATH=", m);
	m->cmd_dirs = ft_split(m->path, ':');
	m->cmd_count = 1; //minimo tenemos un comando
	m->x_index = 0;
	if (!m->cmd_dirs)
		m_exit("Cannot allocate memory in is_it_command");
	i = 0;
	while (m->tokens[i])
	{
		x = 0;
		while (m->tokens[i][x])
		{
			if (m->tokens[i][x++] == '|')
				m->cmd_count++; //por cada pipe que encontramos tendremos un comando adicional.
		}
		i++;
	}
	m->cmds = ft_calloc(m->cmd_count + 1, sizeof(t_command)); //m->cmds apuntara a cada estructura asociada con un comando.
	if (!m->cmds)
		m_exit("Cannot allocate memory in initiate_commands");
	m->cmds[m->cmd_count] = NULL;
}

void	token_assign(t_mini *m) //almacena los comandos en la lista de nodos m->cmds.
{
	int	i;
	int	code; //Su valor varia en función de que era el token anterior. Informa de que debería ser el token actual. Una redirección debería ir seguida de un archivo etc... si es un argumento 0, si es un comando 1, si es un pipe 2 si es una redireccion ... 
	int	cmd_index; //Indica a que comando pertenecen los tokens. Cambia cuando encontramos un '|' .

	i = 0;
	code = 0;
	cmd_index = 0;
	initiate_get_commands(m);
	initiate_command_structs(m);//inicializamos los full_cmd de las t_command.
	while (m->tokens[i] && cmd_index < m->cmd_count)
	{
		code = token_indentify(m->tokens[i], code, cmd_index, m);
		if (code == 2) //si hemos encontrado un pipe
		{
			m->x_index = 0;			
			cmd_index++;
		}
		i++;
	}
}