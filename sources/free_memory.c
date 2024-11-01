/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:33:18 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/01 13:58:54 by dangonz3         ###   ########.fr       */
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
	int	x;
	
	i = 0;
/* 	ft_printf("OLA1\n");
	printf("Dirección de full_cmd[0]: %p\n", (void *)m->cmds[0].full_cmd[0]);
	printf("Dirección de full_path: %p\n", (void *)m->cmds[0].full_path);
	ft_printf("1free_tcommand m->cmds[0].full_path = %s\n", m->cmds[0].full_path); */
	while (i < m->cmd_count)
	{
		x = 0;
		if(m->cmds[i].full_cmd)
		{
/* 			printf("Dirección de full_cmd[0]: %p\n", (void *)m->cmds[0].full_cmd[0]);
			printf("Dirección de full_path: %p\n", (void *)m->cmds[0].full_path);
			ft_printf("2free_tcommand m->cmds[0].full_path = %s\n", m->cmds[0].full_path); */
			while (m->cmds[i].full_cmd[x])
				free(m->cmds[i].full_cmd[x++]);
/* 			printf("Dirección de full_cmd[0]: %p\n", (void *)m->cmds[0].full_cmd[0]);
			printf("Dirección de full_path: %p\n", (void *)m->cmds[0].full_path);
			ft_printf("3free_tcommand m->cmds[0].full_path = %s\n", m->cmds[0].full_path); */
			free(m->cmds[i].full_cmd);
/* 			ft_printf("4free_tcommand m->cmds[0].full_path = %s\n", m->cmds[0].full_path); */
			m->cmds[i].full_cmd = NULL;
/* 			ft_printf("5free_tcommand m->cmds[0].full_path = %s\n", m->cmds[0].full_path); */
		}
/* 		ft_printf("OLA2\n"); */
/* 		if (m->cmds[i].cmd_index)
			ft_printf("m->cmds[%i].cmd_index EXISSTEEE\n", i); */
/* 		ft_printf("m->cmds[%i].full_path = %s\n", i, m->cmds[i].full_path); */
		if(m->cmds[i].full_path)
			free(m->cmds[i].full_path);
/* 		ft_printf("OLA3\n"); */
		free_tcommand_aux(i, m);
/* 		ft_printf("OLA4\n"); */
		i++;		
	}
	m->cmd_count = 0;
	free(m->cmds);
/* 	ft_printf("OLA5\n"); */
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
	if (matrix)
		free(matrix);
}
