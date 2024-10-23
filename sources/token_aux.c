/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:29:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/23 20:55:57 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	identify_token_alt(char *tkn, int code) //Su objetivo es contar el tamaño que deberia tener el full_cmd de cada t_command. Distingue entre cuatro tipos de tokens, el grupo 0 (comando, argumentos y opciones) va en la estructura full_cmd de t_command, el grupo 1 son los '|' que indican que debemos empezar a rellenar el full_cmd de una nueva estructura t_command, el 2 grupo son las redirecciones, el 3 grupo son los argumentos de las redirecciones
{
	if (code == 3) //el anterior token era una redireccion y este debe ser su argumento.
		return (4);	
	else if (!ft_strcmp(tkn, "<") || !ft_strcmp(tkn, "<<") || !ft_strcmp(tkn, ">") || !ft_strcmp(tkn, ">>"))
		return (3);
	else if (!ft_strcmp(tkn, "|"))
		return (2);
	else
		return (1);
}

void	initiate_command_structs(t_mini *m) //su objetivo es alojar memoria para cada m->cmds[].full_cmd.
{
	int	i;
	int	cmd_index;
	int start;
	int code;

	i = 0;
	cmd_index = 0;
	start = 0;
	while (m->tokens[i])
	{
		code = identify_token_alt(m->tokens[i], 0);			
		if (code == 2) //si hemos encontrado un pipe
		{
			m->cmds[cmd_index].full_cmd = ft_calloc(i - start, sizeof(char *));
			cmd_index++;
			start = i + 1; //el proximo full_cmd para slguiente command no empezara con '|' sino con el siguiente token
		}
		i++;
	}
	m->cmds[cmd_index].full_cmd = ft_calloc(i - start, sizeof(char *));
}

void	initiate_get_commands(t_mini *m) //consigue los valores de m->path y m->cmd_dirs. Aloja meoria para m->cmds.
{
	int	i;
	int	x;
	
	m->path = return_envp_var("PATH=", m);

	printf("INITIATE m->path = %s\n", m->path);
	
	m->cmd_dirs = ft_split(m->path, ':');
	if (!m->cmd_dirs)
		m_exit("Cannot allocate memory in initiate_get_commands", m);
	
	i = 0;
	while (m->cmd_dirs[i])
	{
		printf("INITIATE m->cmd_dirs[%d] = %s\n", i, m->cmd_dirs[i]);
		i++;
	}

	
	i = 0;
	m->cmd_count = 1; //minimo tenemos un comando
	m->x_index = 0;
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
	m->cmds = ft_calloc(m->cmd_count, sizeof(t_command)); //m->cmds apuntara a cada estructura asociada con un comando.
	if (!m->cmds)
		m_exit("Cannot allocate memory in initiate_commands", m);
}
