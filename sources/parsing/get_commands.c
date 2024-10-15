/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:29:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/15 17:53:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	get_commands(t_mini *m) //almacena los comandos en la lista de nodos m->cmds.
{
	int	i;
	int	cmd_type; //si es cero no es un comando, si es 1 es built_in, si es 2 es un comando del sistema.
	int	cmds_list_size;

	i = 0;
	initiate_get_commands(m);
	while (m->tokens[i])
	{
		cmd_type = is_it_command(m->tokens[i], m);
		if (cmd_type)
			i = create_node(m->tokens[i], cmd_type, i, m)
		i++;
	}
} */

void	get_commands(t_mini *m) //almacena los comandos en la lista de nodos m->cmds.
{
	int	i;
	int	code; //Su valor varia en función de que era el token anterior. Informa de que debería ser el token actual. Una redirección debería ir seguida de un archivo etc... si es un argumento 0, si es un comando 1, si es un pipe 2 si es una redireccion ... 
	int	cmd_index; //Indica a que comando pertenecen los tokens. Cambia cuando encontramos un '|' .

	i = 0;
	code = 0;
	cmd_index = 0;
	initiate_get_commands(m);
	while (m->tokens[i] && cmd_index <= m->cmd_count)
	{
		code = identify_token(m->tokens[i++], code, cmd_index, m);
		if (code == 2)
			cmd_index++;
	}
}

int	identify_token(char *tkn, int code, int cmd_index, t_mini *m)
{
	if (code == 2) //significa que el token anterior era un pipe y ahora tenemos que redirigir el input del comando actual (hemos pasado al siguiente comando al aumentar cmd_index).
		m->cmds[cmd_index].infile = tkn;
	else if (code > 2)
		return (assign_redirection(tkn, code, cmd_index, m), 0); //indica en la estructura t_command cual es el archivo al que se está redirigiendo.
	else if (tkn == '|')
		return (2);
	else if (tkn == '<')
		return (3);
	else if (tkn == '<<')
		return (4);
	else if (tkn == '>')
		return (5);
	else if (tkn == '>>')
		return (6);
	return (0)
}

void assign_redirection(char *tkn, int code, int cmd_index, t_mini *m)
{
	if (code == 3)
		m->cmds[cmd_index].infile = tkn;
	else if (code == 4)
	{
		m->cmds[cmd_index].append = 1;
		m->cmds[cmd_index].infile = tkn;
	}
	else if (code == 5)
		m->cmds[cmd_index].outfile = tkn;
	else if (code == 6)
	{
		m->cmds[cmd_index].append = 1;
		m->cmds[cmd_index].outfile = tkn;
	}
	else
		m_exit("Error indentyfing tokens in assign_redirection", m);	
}






























void	initiate_get_commands(t_mini *m) //consigue los valores de m->path y m->cmd_dirs. Aloja meoria para m->cmds.
{
	int	i;
	int	x;
	
	m->path = return_envp_var("PATH=", m);
	m->cmd_dirs = ft_split(m->path, ':');
	m->cmd_count = 1; //minimo tenemos un comando
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

/* int	is_it_command(char *tkn, t_mini *m) //comprueba alguno de los tokens es un comando, ya sea built_in o del sistema.
{
	int		i;
	int		j;
	char	*cmd_name;

	i = 0;
	while (m->tokens[i])
	{
		if (is_it_builtin(m->tokens[i], m))
			return (1);
		cmd_name = ft_strjoin("/", m->tokens[i]);
		if (!cmd_name)
			return (m_exit("Cannot allocate memory in is_it_command", 0));
		j = 0;
		while (m->cmd_dirs[j])
		{
			if (!acces(m->cmd_dirs[j++], X_OK))
				return (free(cmd_name), 2);
		}
		free(cmd_name);
		i++;
	}
	return (0);
} */

/* int	is_it_builtin(char *tkn, t_mini *m)
{
	if (ft_strstr(tkn, "echo"))
		return (1);
	else if (ft_strstr(tkn, "cd"))
		return (1);	
	else if (ft_strstr(tkn, "pwd"))
		return (1);
	else if (ft_strstr(tkn, "export"))
		return (1);
	else if (ft_strstr(tkn, "unset"))
		return (1);
	else if (ft_strstr(tkn, "env"))
		return (1);
	else if (ft_strstr(tkn, "exit"))
		return (1);
	return (0);
} */
