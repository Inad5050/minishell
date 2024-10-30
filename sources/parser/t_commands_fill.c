/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_commands_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:16:16 by dani              #+#    #+#             */
/*   Updated: 2024/10/30 19:49:14 by dani             ###   ########.fr       */
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
		if (i == 0 && code != 1)
			return (m_error("First token should be a command", m), 0);
		if (code == 2)
			return (m_error("Incorrect pipe", m), 0);
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
		return (m_error("There should be at least one command", m), 0);
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
	else if (code > 2)
		return (assign_redirection(tkn, code, c->cmd_index, m));
	else if (!ft_strcmp(tkn, "|"))
		return (2);
	else if (!ft_strcmp(tkn, "<"))
		return (3);
	else if (!ft_strcmp(tkn, "<<"))
		return (4);
	else if (!ft_strcmp(tkn, ">"))
		return (5);
	else if (!ft_strcmp(tkn, ">>"))
		return (6);
	else
		return (1);
}

int assign_redirection(char *tkn, int code, int cmd_index, t_mini *m) //rellena infile_name y outfile_name en cada t_command. Más adelante los intentaremos abrir.
{
	if (code == 3 || code == 4)
	{
		if (m->cmds[cmd_index].infile) //si tiene valor es que ya habia una redireccion
			return (m_error("Double input redirection", m), 0);
		m->cmds[cmd_index].infile_name = ft_strdup(tkn);
		if (!m->cmds[cmd_index].infile_name)
			m_exit("Couldn't allocate memory in assign_redirection", m);
		if (code == 4)
			m->cmds[cmd_index].append_in = 1;
	}		
	else if (code == 5 || code == 6)
	{
		if (m->cmds[cmd_index].outfile) //si tiene valor es que ya habia una redireccion
			return (m_error("Double outfile redirection", m), 0);
		m->cmds[cmd_index].outfile_name = ft_strdup(tkn);
		if (!m->cmds[cmd_index].outfile_name)
			m_exit("Couldn't allocate memory in assign_redirection", m); 
		if (code == 6)
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
		return (m_error("Incorrect pipe", m), 0); //falta el segundo comando.
	if (pipe(pipefd) < 0)
		m_exit("Couldn't open pipe on get_pipes", m);	
	m->cmds[cmd_index + 1].infile = pipefd[0];
	if ((m->cmds[cmd_index].outfile_name)) //si outfile_name tiene valor es que ya existia una redireccion del outfile. En este caso el input del user es incorrecto.
		return (m_error("Double output redirection", m), 0);
	m->cmds[cmd_index].outfile = pipefd[1];
	return (1);
}