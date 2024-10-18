/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_indentify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:46:25 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/18 16:30:50 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void assign_redirection(char *tkn, int code, int cmd_index, t_mini *m) //rellena infile_name y outfile_name en cada t_command. Más adelante los intentaremos abrir.
{
	if (code == 3 || code == 4)
	{
		if (m->cmds[cmd_index].infile) //si tiene valor es que ya habia una redireccion
			m_error("Double input redirection", m);
		m->cmds[cmd_index].infile = ft_strdup(tkn);
		if (!m->cmds[cmd_index].infile)
			m_exit("Couldn't allocate memory in assign_redirection", m);
		if (code == 4)
			m->cmds[cmd_index].append_in = 1;
	}		
	else if (code == 5 || code == 6)
	{
		if (m->cmds[cmd_index].outfile) //si tiene valor es que ya habia una redireccion
			m_error("Double outfile redirection", m);
		m->cmds[cmd_index].outfile = ft_strdup(tkn);
		if (!m->cmds[cmd_index].outfile)
			m_exit("Couldn't allocate memory in assign_redirection", m); 
		if (code == 6)
			m->cmds[cmd_index].append_out = 1;
	}		
	else
		m_exit("Incorrect code in assign_redirection", m);
}

void	get_pipes(int cmd_index, t_mini *m)
{
	int	pipefd[2];
	
	if (cmd_index + 1 > m->cmd_count)
		m_error("Incorrect pipe", m); //falta el segundo comando.
	if (pipe(pipefd) < 0)
		m_exit("Couldn't open pipe on get_pipes", m);	
	m->cmds[cmd_index + 1].infile = pipefd[0];
	if ((m->cmds[cmd_index].outfile_name)) //si outfile_name tiene valor es que ya existia una redireccion del outfile. En este caso el input del user es incorrecto.
		m_error("Double output redirection", m);
	m->cmds[cmd_index].outfile = pipefd[1];
}

int	token_indentify(char *tkn, int code, int cmd_index, t_mini *m)
{
	if (code == 2) //significa que el token anterior era un pipe y ahora tenemos que redirigir el input del comando actual (hemos pasado al siguiente comando al aumentar cmd_index).
		get_pipes(cmd_index, m);
	else if (code > 2) //significa que el token anterior redirigia (input o output) al archivo actual.
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
	else
	{
		if (!(m->cmd_dirs[cmd_index].full_cmd[m->x_index]))
			m_exit("Error in identify_token, failure to assign \
			memory in initiate_command_structs", m);
		m->cmd_dirs[cmd_index].full_cmd[m->x_index] = ft_strdup(tkn);
		if (!(m->cmd_dirs[cmd_index].full_cmd[m->x_index]))
			m_exit("Could`t assign memory in identify_token", m);
		m->x_index++; //necesitaba otro indice que mantuviera su valor entre llamadas a la funcion, pero identify_token() ya tiene 4 variables, asi que m->x_index está dentro de la estructura.
	}
	return (0)
}
