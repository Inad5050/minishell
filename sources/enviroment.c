/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:33:51 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/17 19:34:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_enviroment(char **argv, t_prompt *m)
{
	m->cwd = get_cwd(NULL, 0); //consigue la ruta al CurrentWorkingDirectory y crea un string (alloc) para lojar la ruta
	set_enviroment("PWD", m->envp, m); //PrintWorkingDirectory
	set_enviroment("SHLVL", m->envp, m); //en cuantos niveles de shell hemos hecho inception
	set_enviroment("PATH", m->envp, m); //los directorios de los comandos del sistema
	set_enviroment("_", m->envp, m); //nombre del programa o el comando que está ejecutando el proceso actual


}
