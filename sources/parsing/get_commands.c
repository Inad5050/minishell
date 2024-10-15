/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:29:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/14 18:53:07 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_it_builtin(char *tkn, t_mini *m)
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
}

int	is_it_command(char *tkn, t_mini *m) //comprueba alguno de los tokens es un comando, ya sea built_in o del sistema.
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
}

void	initiate_commands(t_mini *m) //consigue los valores de m->path y m->cmd_dirs. Aloja meoria para m->cmds.
{
	int	i;

	i = 0;
	m->path = return_envp_var("PATH=", m);
	m->cmd_dirs = ft_split(m->path, ':');
	if (!m->cmd_dirs)
		return (m_exit("Cannot allocate memory in is_it_command", 0));
	while (m->tokens[i])
		i++;
	m->cmds = ft_calloc(i + 1, sizeof(t_command)); //el número máximo de commands sera el memor al numero de tokens.
	if (!m->cmds)
		m_exit("Cannot allocate memory in initiate_commands");
}

int	create_node(char *tkn, int cmd_type, int index, t_mini *m) //inicializa el nodo asociado con cada comando
{
	t_command	*node;
	int			cmds_list_size;

	node = ft_calloc(1, sizeof(t_command));
	if (!node)
		m_exit("Cannot allocate memory in create_node");
	cmds_list_size = ft_lstsize(m->cmds);
	m->cmds[cmds_list_size] = node;
	node->index = index;
	get_full_cmd(node, tkn, index, m);
	




	
}

int	get_full_cmd(t_command	*node, char *tkn, int index, t_mini *m)
{
	int	previous_command;
	int	next_command;

	while (index)
	{
		if (is_it_command(m->tokens[index--], m)) 
			break;
	}
	previous_command = index;
	while (index)
	{
		if (is_it_command(m->tokens[index++], m)) 
			break;
	}
	next_command = index;


	
}


void	get_commands(t_mini *m) //almacena los comandos en la lista de nodos m->cmds.
{
	int	i;
	int	cmd_type; //si es cero no es un comando, si es 1 es built_in, si es 2 es un comando del sistema.
	int	cmds_list_size;

	i = 0;
	initiate_commands(m);
	while (m->tokens[i])
	{
		cmd_type = is_it_command(m->tokens[i], m);
		if (cmd_type)
			i = create_node(m->tokens[i], cmd_type, i, m)
		i++;
	}
	cmds_list_size = ft_lstsize(m->cmds);
	m->cmds[cmds_list_size] = NULL;
}