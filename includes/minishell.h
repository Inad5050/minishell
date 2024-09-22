/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/22 15:26:23 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include "signal.h" //gestion de señales
#include "sys/ioctl.h" //proporciona las definiciones necesarias para las llamadas a ioctl(), que permiten configurar y controlar dispositivos y terminales.
#include <stdbool.h> // for boolean
extern int g_status; //variable global, da cuenta de la gestión de errores. Si no usamos extern cada vez que otro archivo .c incluya este encabezado, se creará una copia independiente de la variable en cada archivo. 

typedef struct s_mini
{
	t_command	*cmds; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Linked list containing a t_command node with all commands separated by pipes
	char		**envp; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Up-to-date array containing keys and values for the shell environment
	pid_t		pid; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Process ID of the minishell instance
	
	//dani
	char		*prompt;
	char		*input;
	char		**split;

	//otman
	
}			t_mini;

typedef struct s_command
{
	char		**full_cmd; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Equivalent of the typical argv, containing the command name and its parameters when needed
	char		*full_path; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) If not a builtin, first available path for the executable denoted by argv[0] from the PATH variable
	int			infile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to read from when running a command (defaults to stdin)
	int			outfile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to write to when running a command (defaults to stdout)
	t_command	*next;
}			t_command;

/* //cmd_trim
char		**ft_cmdtrim(char const *s, char *set);
static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3]);
static int	ft_count_words(const char *s, char *c, int i[2]);

//enviroment
void		init_enviroment(char **argv, t_mini *m); */

//exit
void	m_exit(char	*str, t_mini *m);

//init_structure
void	init_struct(char **envp, t_mini *m);
void	duplicate_envp(char	**envp, t_mini *m);
void	mini_getpid(t_mini *m);

//parsing
void	*check_args(char *input, t_mini *m);

//signals
void	handle_sigint(int sig);
//Builtin Otmane
void builtin(t_mini *mini);
void echo(t_command *cmd, int fd);
void	env(t_mini *mini);

//errors.c
void	m_error(char	*str, t_mini *m); //imprime un mensaje de error, pero no cierra la minishell. Probablemente lo uses tu Otman. No se si deberia hacer algo más que imprimir el error.

#endif