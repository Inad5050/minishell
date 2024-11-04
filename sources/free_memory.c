/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:33:18 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/04 20:00:48 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer_parser(t_mini *m)
{
	if (m->input)
		m_free(&(m->input));
	if (m->tokens)
		free_matrix(&(m->tokens));
	m->token_count = 0;
	m->in_quotes = 0;
	m->quote_type = 0;
	m->squote = 0;
	m->dquote = 0;
	m->no_path = 0;
	if (m->path)
		m_free(&(m->path));
	if (m->cmd_dirs)
		free_matrix(&(m->cmd_dirs));
	m->post_redirection = 0;
	m->x_index = 0;
	free_lexer_parser_aux(m);
	m->is_blocking = 0;
	m->no_path = 0;
}

void	free_lexer_parser_aux(t_mini *m)
{
	if (m->var_name_with_dollar)
		m_free(&(m->var_name_with_dollar));
	if (m->var_name)
		m_free(&(m->var_name));
	if (m->var_name_envp)
		m_free(&(m->var_name_envp));
	if (m->variable_envp)
		m_free(&(m->variable_envp));
	if (m->variable)
		m_free(&(m->variable));
	if (m->str_pre_var_name)
		m_free(&(m->str_pre_var_name));
	m->var_name_size = 0;
	if (m->str_post_var_name)
		m_free(&(m->str_post_var_name));
	if (m->str_pre_plus_var)
		m_free(&(m->str_pre_plus_var));
	if (m->new_tkn)
		m_free(&(m->new_tkn));
}

void	free_tcommand(t_mini *m)
{
	int	i;
	int	x;

	i = 0;
	while (i < m->cmd_count)
	{
		x = 0;
		if (m->cmds[i].full_cmd)
		{
			while (m->cmds[i].full_cmd[x])
				m_free(&(m->cmds[i].full_cmd[x++]));
			m_free(m->cmds[i].full_cmd);
			m->cmds[i].full_cmd = NULL;
		}
		if (m->cmds[i].full_path)
			m_free(&(m->cmds[i].full_path));
		free_tcommand_aux(i, m);
		i++;
	}
	m->cmd_count = 0;
	free(m->cmds);
	m->cmds = NULL;
}

void	free_tcommand_aux(int i, t_mini *m)
{
	if (m->cmds[i].infile != 0)
		close(m->cmds[i].infile);
	if (m->cmds[i].infile_name)
		m_free(&(m->cmds[i].infile_name));
	if (m->cmds[i].outfile != 1)
		close(m->cmds[i].outfile);
	if (m->cmds[i].outfile_name)
		m_free(&(m->cmds[i].outfile_name));
	if (m->cmds[i].tokens)
		free_matrix(&(m->cmds[i].tokens));
}

void	free_tmini(t_mini *m)
{
	if (m->envp)
		free_matrix(&(m->envp));
	if (m->prompt)
		m_free(&(m->prompt));
	if (m)
		free(m);
}
