/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/18 17:47:40 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "signal.h" //gestion de señales
# include "sys/ioctl.h" //proporciona las definiciones necesarias para las llamadas a ioctl(), que permiten configurar y controlar dispositivos y terminales.
# include <stdbool.h> // for boolean
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h> //opendir, readdir y closedir


extern int g_status; //variable global, da cuenta de la gestión de errores. Si no usamos extern cada vez que otro archivo .c incluya este encabezado, se creará una copia independiente de la variable en cada archivo. 

# define DQ 34
# define SQ 39
# define BACKSLASH 92

typedef struct s_command	t_command;
typedef struct s_mini
{
	t_command	*cmds; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Linked list containing a t_command node with all commands separated by pipes
	
	char		**envp; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Up-to-date array containing keys and values for the shell environment
	pid_t		pid; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Process ID of the minishell instance
	
	char		*prompt; //getprompt (main)
	char		*input; //readline (main)
	char		**tokens; //se usa a para almacenar el inpurt del usuario tras la tokenización del lexeo
	int			token_count; //ft_count_words (lexer)
	int			in_quotes; //ft_count_words (lexer)
	int			quote_type; //ft_count_words (lexer)
	int 		squote; //fill_tokens (lexer)
	int 		dquote; //fill_tokens (lexer)
	char		*path; //initiate_get_commands (get_commands)
	char		**cmd_dirs; //initiate_get_commands (get_commands)
	int			cmd_count; //initiate_get_commands (get_commands)
	int			post_redirection; //initiate_get_commands (get_commands)
	int			x_index; //identify_token (get_commands)
}			t_mini;

typedef struct s_command
{
	char		**full_cmd; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Equivalent of the typical argv, containing the command name and its parameters when needed
	char		*full_path; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) If not a builtin, first available path for the executable denoted by argv[0] from the PATH variable
	int			infile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to read from when running a command (defaults to stdin)
	int			outfile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to write to when running a command (defaults to stdout)
	
	char		*infile_name; //assign_redirection (get_commands)
	char		*outfile_name; //assign_redirection (get_commands)
	int			append_in; // Si es 1, es redirección con append (<<), si es cero es <
	int			append_out; // Si es 1, es redirección con append (>>), si es cero es >
	int			is_builtin; //is_builtin (check_commands)
}			t_command;

/* //cmd_trim
char		**ft_cmdtrim(char const *s, char *set);
static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3]);
static int	ft_count_words(const char *s, char *c, int i[2]);

//enviroment
void		init_enviroment(char **argv, t_mini *m); */

//exit
void	m_exit(char	*str, t_mini *m);

//PARSER

//env_vars
//envp_aux
char	*return_envp_variable(char *str, t_mini *m);
int		find_envp_variable(char *str, int size, t_mini *m);
//eror_code
//getprompt
void	getprompt(t_mini *m);
//init_struct
t_mini	*init_struct(char **envp);
void	init_struct_envp(char **envp, t_mini *m);
void	init_struct_getpid(t_mini *m);
//lexer_aux
int		problematic_chars(char	c, t_mini *m);
int		in_squotes(char	c, t_mini *m);
int		in_dquotes(char	c, t_mini *m);
int		escaped(char c, t_mini *m);
void	free_lexer(t_mini *m);
//lexer
int		lexer(t_mini *m);
int		count_tokens(t_mini *m);
void	fill_split(t_mini *m);
char	*ft_strndup(const char *src, size_t n);
//parser
int		parser(t_mini *m);

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