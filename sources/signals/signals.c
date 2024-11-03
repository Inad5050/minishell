/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:16:11 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/03 16:47:16 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handler_ctrl_quit(int sig)
{
	(void)sig;
		ft_putstr_fd("Quit\n", STDERR_FILENO);
}
 void handler_false(int sig)
{	
	if (sig == SIGINT)
	{	
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void init_signals(int flag)
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
