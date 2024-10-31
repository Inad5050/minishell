/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:33:18 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/31 17:46:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer_parser(t_mini *m)
{
	if (m->input)
		free(m->input); //al parecer no hay que liberar la memoria alojada por readline() ?
	if (m->tokens)
	{
		free_matrix(m->tokens);
		m->tokens = NULL; //es necesario para evitar que el programa vuelva a intentar libera la memoria tras if(!m->tokens)
	}
	m->token_count = 0;
	m->in_quotes = 0;
	m->quote_type = 0;
	m->squote = 0;
	m->dquote = 0;
	if (m->path)
		free(m->path);
	if (m->cmd_dirs)
	{
		free_matrix(m->cmd_dirs);
		m->cmd_dirs = NULL; //es necesario para evitar que el programa vuelva a intentar libera la memoria tras if(!m->cmd_dirs)
	}
	m->post_redirection = 0;
	m->x_index = 0;
}

void	free_tcommand(t_mini *m)
{
	int	i;
	
	i = 0;
	while (i < m->cmd_count)
	{
		if(m->cmds[i].full_cmd)
		{
			free_matrix(m->cmds[i].full_cmd);
			m->cmds[i].full_cmd = NULL;
		}
		if(m->cmds[i].full_path)
			free(m->cmds[i].full_path);
		free_tcommand_aux(i, m);
		i++;		
	}
	m->cmd_count = 0;
	free(m->cmds);
}

void	free_tcommand_aux(int i, t_mini *m)
{
	if(m->cmds[i].infile_name)
	{
		close(m->cmds[i].infile);
		free(m->cmds[i].infile_name);
	}
	if(m->cmds[i].outfile_name)
	{
		close(m->cmds[i].outfile);
		free(m->cmds[i].outfile_name);
	}
	if(m->cmds[i].tokens)
	{
		free_matrix(m->cmds[i].tokens);
		m->cmds[i].tokens = NULL;
	}	
}

void	free_tmini(t_mini *m) //despues de llamar a free_lexer_parser y free_tcommand la única memoria alojada debería ser la de **envp. Dejo la función por si en el futuro tenemos que liberar otras cosas en este punto del programa.
{
	if (m->envp)
		free_matrix(m->envp);
	if (m->prompt)
		free(m->prompt);
	if (m)
		free(m);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}
