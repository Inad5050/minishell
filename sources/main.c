/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:29:53 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/05 18:08:08 by dangonz3         ###   ########.fr       */
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
	free_lexer_parser(m);
	free_tcommand(m);
	return (1);
}
