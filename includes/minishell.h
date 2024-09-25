/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/25 08:30:51 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include "signal.h" //gestion de señales
#include "sys/ioctl.h" //proporciona las definiciones necesarias para las llamadas a ioctl(), que permiten configurar y controlar dispositivos y terminales.
#include <stdbool.h> // for boolean
#include <stdlib.h>  // exit

extern int g_status; //variable global, da cuenta de la gestión de errores. Si no usamos extern cada vez que otro archivo .c incluya este encabezado, se creará una copia independiente de la variable en cada archivo. 

# define DQ 34
# define SQ 39
# define BACKSLASH 92
typedef struct s_mini
{
	t_command	*cmds; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Linked list containing a t_command node with all commands separated by pipes
	char		**envp; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Up-to-date array containing keys and values for the shell environment
	pid_t		pid; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Process ID of the minishell instance
	
	//dani
	char		*prompt;
	char		*input;
	char		**input_split;
	bool		in_squotes;
	bool		in_dquotes;
	bool		escaped;

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

//parsing(DANI)
//envp_aux
char	*return_envp_variable(char *str, t_mini *m);
int		find_envp_variable(char *str, int size, t_mini *m);
//getprompt
void	getprompt(t_mini *m);
//init_struct
t_mini	*init_struct(char **envp);
void	init_struct_envp(char **envp, t_mini *m);
void	init_struct_getpid(t_mini *m);
//parsing
void	*parsing(t_mini *m);
int		count_tokens(t_mini *m);
void	fill_split(t_mini *m);
//parsing_aux
int		problematic_chars(char	c, t_mini *m);
int		in_squotes(char	c, t_mini *m);
int		in_dquotes(char	c, t_mini *m);
int		escaped(char c, t_mini *m);

//signals
void	handle_sigint(int sig);

//Builtin Otmane
void 	builtin(t_mini *mini);
void 	echo(t_command *cmd, int fd);
void	env(t_mini *mini);

//errors.c
void	m_error(char	*str, t_mini *m); //imprime un mensaje de error, pero no cierra la minishell. Probablemente lo uses tu Otman. No se si deberia hacer algo más que imprimir el error.

#endif



/* 
Además de las comillas simples, dobles y el backslash, hay otros caracteres que podrían ser \
relevantes al tokenizar una cadena de entrada en un estilo similar a Bash:
Espacios: Se consideran delimitadores de tokens.
Tabulaciones y nuevas líneas: También son delimitadores.
Paréntesis y corchetes: (, ), {, }, [, ] pueden ser utilizados para agrupar expresiones.
Signos de dólar ($): Utilizados para referirse a variables.
Comillas invertidas (backticks): ` se utilizan en Bash para la expansión de comandos.
Punto y coma (;): Puede usarse para separar comandos.
Operadores de redirección: >, <, >>, << para la entrada/salida.
Operadores lógicos y de comparación: &&, ||, ==, !=, <, >, <=, >= para expresiones condicionales. 
*/

/* 
Comillas Dobles ("):

Permiten la expansión de variables y el uso de caracteres especiales, como el signo de dólar ($).
Los caracteres escapados con un backslash dentro de comillas dobles son interpretados literalmente (por ejemplo, \" se convierte en ").
Comillas Simples ('):

Todo el contenido dentro de las comillas simples se interpreta literalmente. No se realiza ninguna expansión de variables ni se procesan caracteres especiales.
El backslash no tiene ningún efecto dentro de comillas simples; se interpreta como un carácter literal.
Backslash (\):

Se utiliza para escapar caracteres especiales, permitiendo que un carácter que normalmente tendría un significado especial sea tratado como un carácter literal. Por ejemplo, \" dentro de comillas dobles produce un ", pero \' dentro de comillas simples se interpreta como '.
En Bash, el backslash también puede utilizarse para dividir una línea larga en varias líneas, permitiendo que el comando continúe en la siguiente línea.
 */