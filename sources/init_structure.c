/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:56 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/19 18:56:34 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(char **envp, t_mini *m)
{
	int	i;
	
	i = 0;
	while (envp[i])
		i++;
	m->envp = ft_calloc(i + 1, sizeof(char *));
	if (!m->envp[i])
		m_exit("Couldnt allocate memory for m->envp", m);
	envp[i] = NULL;
	duplicate_envp(envp, m);  //duplica envp para luego modificar la copia y crear la envp de la mini
	mini_getpid(m); //usa fork para conseguir el pid del proceso padre. el hijo termna liberando toda su memoria
	modify_envp(m); //altera envp con los valores de la minishell
}

void	duplicate_envp(char	**envp, t_mini *m)
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
}

void	mini_getpid(t_mini *m)
{
	pid_t	pid;
	pid = fork();
	if (pid < 0)
		m_exit("Couldnt fork()", m);
	if (pid == 0)
		m_exit("Child process", m); //para eliminar al hijo, probablemente haya que crear una excepcion en m_exit para que no imprima nada en este caso
	else
		m->pid = pid;
	return (1);
}

void	modify_envp(t_mini *m)
{
	//modify PWD
	modify_envp_pwd(m);
	










	
}

int	find_envp_variable(char *str, int size, t_mini *m)
{
	int		i;
	
	i = 0;
	while (m->envp[i])
	{
		if (ft_strncmp(m->envp[i], str, size))
			return (i);
		i++;
	}
	return (-1);
}

modify_envp_pwd(t_mini *m)
{
	int		i;
	char	*pwd;
	
	i = find_envp_variable("PWD=", 4, m);
	if (i < 0)
		m_exit("Cannot find envp variable", m); //si se llama a esta funcion en mitad de la ejecucion probablemente no habria que llamara a exit y en su lugar haya que llamar a m_error
	free(m->envp[i]);
	pwd = getcwd(NULL, 0); //NULL y 0 permiten que getcwd asigne dinámicamente el buffer con el tamaño adecuado.
	if (!pwd)
		m_exit("Couldn't execute getcwd", m);
	m->envp[i] = pwd;
	
}

