/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/28 22:48:25 by dani             ###   ########.fr       */
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
# include <stdlib.h> 
# include <sys/wait.h>

extern int g_status; //variable global, da cuenta de la gestión de errores. Si no usamos extern cada vez que otro archivo .c incluya este encabezado, se creará una copia independiente de la variable en cada archivo. 

# define DQ 34
# define SQ 39
# define BACKSLASH 92
# define PATH_MAX 4096 

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
	int			post_redirection; //initiate_get_commands (get_commands)
	int			x_index; //identify_token (get_commands)

	int			cmd_count; //initiate_get_commands (get_commands)   USE
}			t_mini;

typedef struct s_command
{
	char		**full_cmd; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Equivalent of the typical argv, containing the command name and its parameters when needed          USE
	char		*full_path; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) If not a builtin, first available path for the executable denoted by argv[0] from the PATH variable     USE 
	int			infile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to read from when running a command (defaults to stdin)                          USE
	int			outfile; //VARIABLE ORIGINAL (no añadida por Dani, NO BORRAR!) Which file descriptor to write to when running a command (defaults to stdout)                       USE
	
	int			append_in; // Si es 1, es redirección con append (<<), si es cero es <          USE
	int			append_out; // Si es 1, es redirección con append (>>), si es cero es >         USE
	int			is_builtin; //is_builtin (check_commands)                                      USE
	
	char		*infile_name; //assign_redirection (get_commands)
	char		*outfile_name; //assign_redirection (get_commands)

	t_command	*next;
}			t_command;

//check_commands
int		check_commands(t_mini *m);
int		is_builtinn(char *cmd);
int		get_cmd_path(char *cmd_name, t_mini *m);
char	*cmd_path(char **cmd_name, t_mini *m);

//envp_aux
char	*return_envp_var(char *str, t_mini *m); 
int		find_envp_var(char *str, int size, t_mini *m);

//errors
void	m_error(char *str, t_mini *m);
void	m_exit(char *str, t_mini *m);
void	m_exit_modified(char *str, t_mini *m);

//expand_vars
char	*get_expanded_str(char *variable, char *var_name, char *tkn, t_mini *m);
void	get_env_var(char *tkn, int index, t_mini *m);
int		expand_var(int index, t_mini *m);
char	*ft_strstr(char *hay, char *ndle);

//free_memory
void	free_lexer_parser(t_mini *m);
void	free_tcommand(t_mini *m);
void	free_tmini(t_mini *m); 
void	free_matrix(char **matrix);

//getprompt
int		getprompt(t_mini *m);

//init_struct
t_mini	*init_struct(char **envp);
void	init_struct_envp(char **envp, t_mini *m);
void	init_struct_getpid(t_mini *m);

//lexer
void	fill_tokens(char *s, t_mini *m);
int		ft_count_tokens(char *s, t_mini *m);
int		lexer(t_mini *m);

//main
int		main(int argc, char **argv, char **envp);
int		manage_input(t_mini *m);
void 	superprinter(t_mini *m);

//open_files
void 	here_doc(char *end, int i, t_mini *m);
char	*m_get_next_line(int fd, char *end_s);
int		m_strncmp(const char *str1, const char *str2, size_t n);
int		open_files_aux(char *file, int is_outfile, int i, t_mini *m);
int		open_files(t_mini *m);

//parser
int		parser(t_mini *m);

//token_aux
int		identify_token_alt(char *tkn, int code);
void	initiate_command_structs(t_mini *m);
void	initiate_cmds_array(t_mini *m);

//token_indentify
int 	assign_redirection(char *tkn, int code, int cmd_index, t_mini *m);
int		get_pipes(int cmd_index, t_mini *m);
int		token_indentify(char *tkn, int code, int cmd_index, t_mini *m);
int		token_assign(t_mini *m);

// execution
char 	*get_path_from_env(t_mini *mini);
void 	analizing_command(t_mini *mini);
void 	handle_multiple_command(t_mini *mini);
void 	execute_single_command(t_mini *mini);
void 	handle_input_redirection(t_command *cmd, t_mini *mini);
void 	handle_output_redirection(t_command *cmd, t_mini *mini);

//builtin
int		builtin(t_mini *mini);
int 	builtin_cd(t_command *cmd, t_mini *mini);
int 	echo(t_command *cmd, int outfile);
int		env(t_mini *mini, int outfile);
int 	export_var(char *var_value, int outfile, t_mini *mini);
int		built_pwd(int fd, char **envp);
char	*get_env(char **envp, char *name);
int		unset(t_command *cmd, t_mini *mini);
int		exit_builtin(t_command *cmd, t_mini *mini);

#endif
