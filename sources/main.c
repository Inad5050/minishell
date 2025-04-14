/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:29:53 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/06 17:37:22 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	g_ctrl_c_flag;

void	handle_true(int sig)
{
	if (sig == SIGINT)
	{
		g_ctrl_c_flag = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handler_false(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, handler_false);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 1)
	{
		signal(SIGINT, handle_true);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*m;

	m = init_struct(envp);
	if (!m)
		return (1);
	if (!getprompt(m))
		return (1);
	init_signals(1);
	while (argc && argv)
	{
		g_ctrl_c_flag = 0;
		m->input = readline(m->prompt);
		if (g_ctrl_c_flag)
		{
			continue ;
		}
		if (manage_input(m) == -1)
			break ;
	}
	free_tmini(m);
	return (0);
}

int	manage_input(t_mini *m)
{
	if (!m->input)
		return (ft_printf("exit\n"), -1);
	if (!check_user_input(m))
		return (1);
	if (ft_strlen(m->input) > 0)
		add_history(m->input);
	if (!lexer(m))
		return (0);
	if (!parser(m))
		return (0);
	analizing_command(m);
	superprinter(m);
	free_lexer_parser(m);
	free_tcommand(m);
	return (1);
}

void superprinter(t_mini *m)
{
	int	i;
	int	x;

	ft_printf("\n-------------------SUPERPRINTER-------------------\n");
	ft_printf("m->cmd_count = %d\n\n", m->cmd_count);
	i = 0;
	while (m->tokens[i])
	{
		ft_printf("m->tokens[%i] = %s\n", i, m->tokens[i]);
		i++;
	}
	
	i = 0;
	while (i < m->cmd_count)
	{
		ft_printf("\n------------COMAND %d-------------\n", i);
		x = -1;
		while(m->cmds[i].full_cmd[++x])
			ft_printf("full_cmd[%d] = %s\n", x, m->cmds[i].full_cmd[x]);
		ft_printf("full_path = %s\n", m->cmds[i].full_path);
		ft_printf("infile = %i\n", m->cmds[i].infile);
		ft_printf("outfile = %i\n", m->cmds[i].outfile);
		if (m->cmds[i].next)
			ft_printf("m->cmds[%i].next->cmd_index = %i\n", i, m->cmds[i].next->cmd_index);
		else
			ft_printf("m->cmds[%i].next = is NULL\n", i);
		if (m->cmds[i].infile_name)
			ft_printf("infile_name = %s\n", m->cmds[i].infile_name);
		if (m->cmds[i].outfile_name)
			ft_printf("outfile_name = %s\n", m->cmds[i].outfile_name);		
		if (m->cmds[i].append_in)
			ft_printf("append_in = %d\n", m->cmds[i].append_in);
		if (m->cmds[i].append_out)
			ft_printf("append_out = %d\n", m->cmds[i].append_out);
		if (m->cmds[i].is_builtin)
			ft_printf("is_builtin = %d\n", m->cmds[i].is_builtin);
		i++;
	}
	ft_printf("-------------SUPERPRINTER_END-------------------\n\n");
}