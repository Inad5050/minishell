/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:29:53 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/03 16:51:08 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;


static int ctrl_c_flag = 0;
// void handler_ctrl_quit(int sig)
// {
// 	(void)sig;
// 	if(flagg)
// 	{
// 		ft_putstr_fd("Quit\n", STDERR_FILENO);
// 	}
// }
void handle_true(int sig)
{
	if (sig == SIGINT)
	{	
		ctrl_c_flag = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
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

int	main(int argc, char **argv, char **envp)
{
	t_mini	*m;

	g_status = 0;
	m = init_struct(envp); //inicializa las estructuras
	if (!m)
		return (1);
	if (!getprompt(m))
		return (1);
	init_signals(1);
	while (argc && argv) //siempre deberia ser verdadera. Similar a poner (1), pero maneja el error improbable de que argv y/o argc no existan
	{
		ctrl_c_flag = 0;
		m->input = readline(m->prompt); //lee el input del usuario, recibe el promp inicial como argumento
		if (ctrl_c_flag)
		{	
			continue; // Skip further processing if Ctrl-C was pressed
		}
		if (manage_input(m) == -1) //procesa el input del usuario para poder ejecutarlo
			break ;
	}
	free_tmini(m); //el argumento de exit es el código de salida del programa. g_status es la variable global donde se almacenan los errores.
	return (0);
}

int	manage_input(t_mini *m)
{
	if (!m->input)
		return (ft_printf("exit\n"), -1); //cuando el puntero del usuario es NULL terminamos la mini. Es este el comportamiento esperado?
	if (!check_user_input(m))
		return (1);
	if (ft_strlen(m->input) > 0)
		add_history(m->input); //función del sistema relacinada con la gestión de read_line. Añade el argumento a la lista del historial de read_line. Se usa write_history para guardar el historial en el archivo seleccionado. Y read_history para leerlo.
	if (!lexer(m))
		return (0);
	if (!parser(m))
		return (0);
	superprinter(m);
	analizing_command(m);
	free_lexer_parser(m); //libera toda la memoria asociada con el lexer y el parser.
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
