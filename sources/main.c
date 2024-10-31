/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:29:53 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/31 19:13:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	*m;

	g_status = 0;
	m = init_struct(envp); //inicializa las estructuras
	if (!m)
		return (1);
	if (!getprompt(m))
		return (1);
	while (argc && argv) //siempre deberia ser verdadera. Similar a poner (1), pero maneja el error improbable de que argv y/o argc no existan
	{
		m->input = readline(m->prompt); //lee el input del usuario, recibe el promp inicial como argumento
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
	if (ft_strlen(m->input) > 0)
		add_history(m->input); //función del sistema relacinada con la gestión de read_line. Añade el argumento a la lista del historial de read_line. Se usa write_history para guardar el historial en el archivo seleccionado. Y read_history para leerlo.
	if (!lexer(m))
		return (0);
	if (!parser(m))
		return (0);
	/* superprinter(m); */
	analizing_command(m);
	free_lexer_parser(m); //libera toda la memoria asociada con el lexer y el parser.
	free_tcommand(m); 
	return (1);
}

void superprinter(t_mini *m) //para pruebas
{
	int	i;
	int	x;

	i = 0;
	ft_printf("-------------------SUPERPRINTER-------------------\n");
	ft_printf("m->cmd_count = %d\n", m->cmd_count);
	
	while (i < m->cmd_count)
	{
		ft_printf("\n------------COMANDO %d-------------\n", i);
		x = -1;
		while(m->cmds[i].full_cmd[++x])
			ft_printf("full_cmd[%d] = %s\n", x, m->cmds[i].full_cmd[x]);
		ft_printf("full_path = %s\n", m->cmds[i].full_path);
		ft_printf("infile = %i\n", m->cmds[i].infile);
		ft_printf("outfile = %i\n", m->cmds[i].outfile);
		if (m->cmds[i].next->cmd_index)
			ft_printf("OLAA m->cmds[%i].next->cmd_index = %i\n", i, m->cmds[i].next->cmd_index);
		else
			ft_printf("OLAA m->cmds[%i].next->cmd_index = is NULL\n", i);
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
	ft_printf("-------------------END-------------------\n\n");
}
