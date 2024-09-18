/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/18 19:15:14 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/libft.h"
#include "signal.h" //gestion de señales
#include "sys/ioctl.h" //proporciona las definiciones necesarias para las llamadas a ioctl(), que permiten configurar y controlar dispositivos y terminales.

extern int g_status; //variable global, da cuenta de la gestión de errores. Si no usamos extern cada vez que otro archivo .c incluya este encabezado, se creará una copia independiente de la variable en cada archivo. 

typedef struct s_prompt
{
	t_list	*cmds; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Linked list containing a t_mini node with all commands separated by pipes
	char	**envp; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Up-to-date array containing keys and values for the shell environment
	pid_t	pid; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Process ID of the minishell instance
	
	char	*cwd;
	char	*prompt;
	char	*input;
	char	**split;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Equivalent of the typical argv, containing the command name and its parameters when needed
	char	*full_path; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) If not a builtin, first available path for the executable denoted by argv[0] from the PATH variable
	int		infile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to read from when running a command (defaults to stdin)
	int		outfile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to write to when running a command (defaults to stdout)
}			t_mini;

//cmd_trim
char		**ft_cmdtrim(char const *s, char *set);
static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3]);
static int	ft_count_words(const char *s, char *c, int i[2]);

//enviroment
void		init_enviroment(char **argv, t_prompt *m);

//exit
void		m_exit();

//init_structure
t_prompt	*init_struct(char **argv, char **envp, t_prompt	*m);

//parsing
void		*check_args(char *input, t_prompt *m);

//error
void		m_error(char *str);

#endif