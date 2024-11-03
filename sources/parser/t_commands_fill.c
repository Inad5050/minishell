/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_commands_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:16:16 by dani              #+#    #+#             */
/*   Updated: 2024/11/03 01:06:50 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	t_commands_fill(t_command *c, t_mini *m)
{
	int	i;
	int	x;
	int	code;
	
	i = 0;
	x = 0;
	code = 0;
	if (!allocate_full_cmd(c, m))
		return (0);
	while (c->tokens[i])
	{
		code = token_indentify(c->tokens[i], code, c, m);
		if (code == 0)
			return (0);
		if (i == 0 && code != 1)
			return (m_err("First token should be a command", 127, m), 0);
		if (code == 2)
			return (m_err("Incorrect pipe", 2, m), 0);
		if (code == 1)
		{
			c->full_cmd[x] = ft_strdup(c->tokens[i]);
			if (!c->full_cmd[x])
				return (m_exit("Couldn't alloc in fill_t_command", m), 0);
			x++;
		}
		i++;
	}
	return (1);
}

int	allocate_full_cmd(t_command *c, t_mini *m)
{
	int	i;
	int	size;

	i = 0;
	size = 0;	
	while (c->tokens[i])
	{
		if (!(!ft_strcmp(c->tokens[i], "|") || !ft_strcmp(c->tokens[i], "<") || \
    	!ft_strcmp(c->tokens[i], "<<") || !ft_strcmp(c->tokens[i], ">") || \
    	!ft_strcmp(c->tokens[i], ">>")))
			size++;
		i++;
	}
	if (!size)
		return (m_err("There should be at least one command", 127, m), 0);
	c->full_cmd = ft_calloc(size + 1, sizeof(char *));
	if (!c->full_cmd)
		return (m_exit("Couldn't allocate memory in allocate_full_cmd", m), 0);
	c->full_cmd[size] = NULL;
	return (1);
}

int	token_indentify(char *tkn, int code, t_command *c, t_mini *m)
{
	if (code == 2)
		return (get_pipes(c->cmd_index, m));
	else if (code > 3)
	{
		if (!assign_redirection(tkn, code, c->cmd_index, m))
			return (0);
		return (3);
	}
	else if (!ft_strcmp(tkn, "|"))
		return (2);
	else if (!ft_strcmp(tkn, "<"))
		return (4);
	else if (!ft_strcmp(tkn, "<<"))
		return (5);
	else if (!ft_strcmp(tkn, ">"))
		return (6);
	else if (!ft_strcmp(tkn, ">>"))
		return (7);
	else
		return (1);
}

int assign_redirection(char *tkn, int code, int cmd_index, t_mini *m) //rellena infile_name y outfile_name en cada t_command. Más adelante los intentaremos abrir.
{
	if (code == 4 || code == 5)
	{
		if (m->cmds[cmd_index].infile) //si tiene valor es que ya habia una redireccion
			return (m_err("Double input redirection", 2, m), 0);
		m->cmds[cmd_index].infile_name = ft_strdup(tkn);
		if (!m->cmds[cmd_index].infile_name)
			m_exit("Couldn't allocate memory in assign_redirection", m);
		if (code == 5)
			m->cmds[cmd_index].append_in = 1;
	}		
	else if (code == 6 || code == 7)
	{
		if (m->cmds[cmd_index].outfile_name) //si tiene valor es que ya habia una redireccion
			return (m_err("Double outfile redirection", 2, m), 0);
		m->cmds[cmd_index].outfile_name = ft_strdup(tkn);
		if (!m->cmds[cmd_index].outfile_name)
			m_exit("Couldn't allocate memory in assign_redirection", m); 
		if (code == 7)
			m->cmds[cmd_index].append_out = 1;
	}		
	else
		m_exit("Incorrect code in assign_redirection", m);
	return (1);
}

int	get_pipes(int cmd_index, t_mini *m)
{
	int	pipefd[2];
	
	if (cmd_index + 1 > m->cmd_count)
		return (m_err("Incorrect pipe", 1, m), 0); //falta el segundo comando.
	if (pipe(pipefd) < 0)
		m_exit("Couldn't open pipe on get_pipes", m);	
	m->cmds[cmd_index + 1].infile = pipefd[0];
	if ((m->cmds[cmd_index].outfile_name)) //si outfile_name tiene valor es que ya existia una redireccion del outfile. En este caso el input del user es incorrecto.
		return (m_err("Double output redirection", 1, m), 0);
	m->cmds[cmd_index].outfile = pipefd[1];
	return (1);
}