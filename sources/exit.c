/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:35:33 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/20 17:16:34 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_exit(char	*str, t_mini *m) //imprime un mensaje de error y cierra el programa
{
	ft_putstr_fd(str, 2); //imprime el mensaje de error en la STDERR
	ft_putstr_fd("\n", 2); //imprime el mensaje de error en la STDERR
	free_memory(m);
}

void	free_memory(t_mini *m) //comprueba que memoria hemos alojado y la libera, se le debería poder llamar desde cualquier parte del programa. Si usas mutex (creo que no hace falta) puedes crear un boolano que pasa a ser true cuando creas el mutex, ese boolano lo podemos usar en esta funcion para saber que tenemos que destruir el mutex.
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	free_memory_commands(m);
	while (m->envp[i]) //envp acaba en NULL, podemos iterar sobre ella como si fuera un string
	{
		j = 0;
		while (m->envp[i][j])
			free(m->envp[i][j++]);
		free(m->envp[i++]);		
	}
	free_memory_parsing(m); //libera la memoria de las variables creadas por dani
	free_memory_execution(m); //libera la memoria de las variables creadas por otman
	exit(g_status);	//cierra el programa con el valor de la variable global, que señala los errores 
}

void	free_memory_commands(t_mini *m) //libera la memoria de cada commandm, y cierra los filedescriptors
{
	t_command	*index;
	int			i;
	
	if (!m->cmds)
		return;
	index = m->cmds;
	while (index)
	{
		i = 0;
		while (index->full_cmd[i])
			free(index->full_cmd[i++]);
		free(index->full_cmd);		





		if (!(index->next))
			break;
	}
	free(m->cmds);
}

free_memory_parsing(t_mini *m)
{
	if (m->cwd)
		free(m->cwd);
	if (m->prompt)
		free(m->cwd);	
	if (m->cwd)
		free(m->cwd);	
}

free_memory_execution(m);
















/* void	free_memory_commands(t_mini *m) //libera la memoria de cada commandm, y cierra los filedescriptors
{
	int	i;
	int	j;
	
	i = 0;
	if (!m->number_of_commands_executed)
		return;
	while (i < m->number_of_commands_executed)
	{
		j = 0;
		if (m->cmds[i].full_cmd)
		{
			while (m->cmds[i].full_cmd[j])
				free(m->cmds[i].full_cmd[j++]);
			free(m->cmds[i].full_cmd);					
		}
		if (m->cmds[i].full_path)
			free(m->cmds[i].full_path);
		if (m->cmds[i].infile)
			close(m->cmds[i].infile);
		if (m->cmds[i].outfile)
			close(m->cmds[i].outfile);		
	}
	free(m->cmds);
} */