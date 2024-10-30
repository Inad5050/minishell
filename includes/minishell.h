/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/30 22:57:32 by dani             ###   ########.fr       */
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
	
	char		**tokens;
	int			cmd_index;

	t_command	*next;
}			t_command;

//check_commands
int		check_commands(t_mini *m);
int		is_builtinn(char *cmd);
int		get_cmd_path(char *cmd_name, t_mini *m);
void	get_envp_cmd_dirs(t_mini *m);
int		sum_path_to_cmd(t_command *c, t_mini *m);

//envp_aux
char	*return_envp_var(char *str, t_mini *m); 
int		find_envp_var(char *str, int size, t_mini *m);

//expand_vars
char	*get_expanded_str(char *variable, char *var_name, char *tkn, t_mini *m);
void	get_env_var(char *tkn, int index, t_mini *m);
int		expand_var(int index, t_mini *m);
char	*ft_strstr(char *hay, char *ndle);

//getprompt
int		getprompt(t_mini *m);

//here_doc
void 	here_doc(char *end, int i, t_mini *m);
char	*m_get_next_line(int fd, char *end_s);
int		m_strncmp(const char *str1, const char *str2, size_t n);

//init_struct
t_mini	*init_struct(char **envp);
void	init_struct_envp(char **envp, t_mini *m);

//lexer
void	fill_tokens(char *s, t_mini *m);
int		ft_count_tokens(char *s, t_mini *m);
int		lexer(t_mini *m);

//open_files
int		open_files_aux(char *file, int is_outfile, int i, t_mini *m);
int		open_files(t_mini *m);

//parser
int		parser(t_mini *m);
int		m_strlen(char **str);

//t_commands_fill
int		t_commands_fill(t_command *c, t_mini *m);
int		allocate_full_cmd(t_command *c, t_mini *m);
int		token_indentify(char *tkn, int code, t_command *c, t_mini *m);
int	 	assign_redirection(char *tkn, int code, int cmd_index, t_mini *m);
int		get_pipes(int cmd_index, t_mini *m);

//t_commands
int		t_commands(t_mini *m);
void	count_commands(t_mini *m);
int		fill_tokens_t_command(t_mini *m);
int		fill_tokens_t_command_aux(int i, int cmd_i, int start, t_mini *m);

//token_check
int		token_check(t_mini *m);
int		check_problem_chars(t_mini *m);
int		check_problem_chars_aux(char tkn, int dquote, int squote, t_mini *m);
int		check_pipes(t_mini *m);
int		check_redirections(t_mini *m);

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
int 	export_var(const char *arg, int outfile, t_mini *mini) ;
int 	built_pwd(int outfile) ;
char	*get_env(char **envp, char *name);
int		unset(t_command *cmd, t_mini *mini);
int		exit_builtin(t_command *cmd, t_mini *mini);

//errors
void	m_error(char *str, t_mini *m);
void	m_error_alt(char c, t_mini *m);
void	m_exit(char *str, t_mini *m);
void	m_exit_modified(char *str, t_mini *m);

//free_memory
void	free_lexer_parser(t_mini *m);
void	free_tcommand(t_mini *m);
void	free_tmini(t_mini *m); 
void	free_matrix(char **matrix);

//main
int		main(int argc, char **argv, char **envp);
int		manage_input(t_mini *m);
void 	superprinter(t_mini *m);

#endif
