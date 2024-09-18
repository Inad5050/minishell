/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:56 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/18 16:50:25 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*init_struct(char **argv, char **envp, t_prompt	*m)
{
	m->envp = duplicate_envp(envp);  //duplica envp para modificar la copia y crear la envp de la mini
	m->pid = mini_getpid(); //usa fork para conseguir el pid del proceso padre. el hijo termna liberando toda su memoria
	init_enviroment(argv, m); //altera envp con los valores de la minishell
	return (m);
}

