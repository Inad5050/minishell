/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:33:18 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/27 17:55:21 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer_parser(t_mini *m)
{
	int	i;
	
/* 	if (m->prompt)
		free(m->prompt); */
	if (m->input)
		free(m->input);
	i = 0;

	/* ft_printf("free_lexer_parser1 m->token_count = %i\n", m->token_count); */
	
	if (m->tokens && i < m->token_count)
		free(m->tokens[i++]);
	free(m->tokens);

	/* ft_printf("free_lexer_parser2\n"); */
	
	m->token_count = 0;
	m->in_quotes = 0;
	m->quote_type = 0;
	m->squote = 0;
	m->dquote = 0;
	if (m->path)
		free(m->path);
	if (m->cmd_dirs)
		free_matrix(m->cmd_dirs);
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
			free_matrix(m->cmds[i].full_cmd);
		if(m->cmds[i].full_path)
			free(m->cmds[i].full_path);
		if(m->cmds[i].infile)
			close(m->cmds[i].infile);
		if(m->cmds[i].outfile)
			close(m->cmds[i].outfile);
		if(m->cmds[i].infile_name)
			free(m->cmds[i].infile_name);
		if(m->cmds[i].outfile_name)
			free(m->cmds[i].outfile_name);
		i++;		
	}
	m->cmd_count = 0;
	free(m->cmds);
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
		free(matrix[i++]);
	free(matrix);	
}