/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:56 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/22 15:23:44 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*init_struct(char **envp)
{
	t_mini	*m;
	int		i;
	
	i = 0;
	g_status = 0; //variable global para recepcion de señales y errores
	m = ft_calloc(1, sizeof(m));
	if (!m)
		return(perror("Couldn't allocate memory for t_prompt m"), NULL);
	while (envp[i])
		i++;
	m->envp = ft_calloc(i + 1, sizeof(char *));
	if (!m->envp[i])
		m_exit("Couldnt allocate memory for m->envp", m);
	envp[i] = NULL;
	init_struct_envp(envp, m); //duplica envp para luego modificar la copia y crear la envp de la mini
	init_struct_getpid(m); //usa fork para conseguir el pid del proceso padre. el hijo termna liberando toda su memoria
	return (m);
}

void	init_struct_envp(char **envp, t_mini *m) //duplica las variables de entorno para poder modificar la copia durante la ejecución de los comandos
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			j++;
		m->envp[i] = ft_calloc(j + 1, sizeof(char));
		if (!m->envp[i])
			m_exit("Couldnt allocate memory for m->envp[i]", m);
		j = 0;
		while (envp[i][j])
		{
			m->envp[i][j] = envp[i][j];
			j++;
		}
		m->envp[i][j] = '\0';
		i++;
	}
	envp[i] = NULL;
}

void	init_struct_getpid(t_mini *m)
{
	pid_t	pid;
	pid = fork();
	if (pid < 0)
		m_exit("Couldnt fork()", m);
	if (pid == 0)
		m_exit("Child process", m); //para eliminar al hijo, probablemente haya que crear una excepcion en m_exit para que no imprima nada cuando reciba la string "Child process"
	else
		m->pid = pid;
	return (1);
}
