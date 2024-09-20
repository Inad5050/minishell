/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:29:53 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/20 16:47:57 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	*m;

	m = ft_calloc(1, sizeof(m));
	if (!m)
		return(perror("Couldn't allocate memory for t_prompt m"), 1);
	g_status = 0; //variable global para recepcion de señales y errores
	init_struct(envp, m); //inicializa las estructuras
	while (argc && argv) //siempre deberia ser verdadera. Similar a poner (1), pero maneja el error improbable de que argv y/0argc no existan
	{
		signal(SIGINT, handle_sigint); //signal se usa para manejar señales. SIGINIT gestiona Ctrl+C. Normalmente se usa para interrumpir el proceso actual (si el segundo argumento de signal es SIG_DFL la señal hara us funcion habitual). handle_sigint es una funcion personalizada con la firma void (*)(int). Cuando reciba la señal del primer argumento el programa ejecutara la funcion del segundo argumento.
		signal(SIGQUIT, SIG_IGN); //SIG_IGN se usa para ignorar la señal del primer argumento.
		m->prompt = getprompt(m); //consigue el prompt de la consola (la línea antes del input del usuario) al estilo de "guest@minishell $ "
		if (m->prompt)
			m->input = readline(m->prompt); //lee el input del usuario, recibe el promp inicial como argumento
		else
			m->input = readline("guest@minishell $ "); //si no consigue el prompt inicial usa uno generico
		if (!check_args(m)) //procesa el input del usuario para poder ejecutarlo
			break ;
	}
	free_memory(m); //el argumento de exit es el código de salida del programa. g_status es la variable global donde se almacenan los errores.
	return (0);
}

