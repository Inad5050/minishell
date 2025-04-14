/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:31:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/11/05 17:44:49 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "signal.h"
# include "sys/ioctl.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h> 
# include <sys/wait.h>

# define DQ 34
# define SQ 39
# define BACKSLASH 92
# define PATH_MAX 4096 

typedef struct s_command
{
	char				**full_cmd;
	char				*full_path;
	int					infile;
	int					outfile;
	int					append_in;
	int					append_out;
	int					is_builtin;
	char				*infile_name;
	char				*outfile_name;
	char				**tokens;
	int					cmd_index;
	struct s_command	*next;
	struct s_mini		*ptr_mini;
}			t_command;

typedef struct s_mini
{
	t_command	*cmds;
	char		**envp;
	int			g_status;
	char		*prompt; //getprompt (main)
	char		*input; //readline (main)
	char		**tokens;
	int			token_count; //ft_count_words (lexer)
	int			in_quotes; //ft_count_words (lexer)
	int			quote_type; //ft_count_words (lexer)
	int			squote; //fill_tokens (lexer)
	int			dquote; //fill_tokens (lexer)
	char		**cmd_dirs; //initiate_get_commands (get_commands)
	int			post_redirection; //initiate_get_commands (get_commands)
	int			x_index; //identify_token (get_commands)
	char		*str_var_name; //expand_vars
	char		*var_name_with_dollar; //expand_vars
	char		*var_name; //expand_vars
	char		*var_name_envp; //expand_vars
	char		*variable_envp; //expand_vars
	char		*variable; //expand_vars
	char		*var_name_ptr; //expand_vars
	char		*str_pre_var_name; //expand_vars
	int			var_name_size; //expand_vars
	char		*str_post_var_name; //expand_vars
	char		*str_pre_plus_var; //expand_vars
	char		*new_tkn; //expand_vars
	char		*tkn; //expand_vars
	int			is_blocking;
	int			no_path; //check_path_env
	int			cmd_count; //initiate_get_commands (get_commands)
}			t_mini;

//check_commands
int		check_commands(t_mini *m);
int		is_builtin_alt(char *cmd);
int		check_cmd_plus_route(int i, t_mini *m);
int		get_cmd_path(char *cmd_name, t_mini *m);
int		sum_path_to_cmd(t_command *c, t_mini *m);

//delete_quotes
int		delete_quotes(t_mini *m);
int		delete_squotes(int i, t_mini *m);
int		delete_dquotes(int i, t_mini *m);
int		check_export(int i, t_mini *m);

//envp_aux
char	*return_envp_var(char *str, t_mini *m);
int		find_envp_var(char *str, int size, t_mini *m);

//expand_vars
int		expand_var(int index, t_mini *m);
int		exchange_token_expansion(char *tkn, t_mini *m);
int		exchange_token_expansion_aux(char *tkn, t_mini *m);
int		exchange_token_expansion_aux_aux(char *tkn, t_mini *m);

//getprompt
int		getprompt(t_mini *m);

//here_doc
void	here_doc(char *end, int i, t_mini *m);
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

//others
int		check_user_input(t_mini *m);
int		get_envp_cmd_dirs(t_mini *m);
int		dont_open_another_mini(t_mini *m);

//parser
int		parser(t_mini *m);

//pre_check_commands
int		pre_check_commands(t_mini *m);
void	check_built_in(t_mini *m);
int		is_builtin_alt(char *cmd);
int		check_path_env(t_mini *m);
int		is_path_avaiable(char *str, int size, t_mini *m);

//t_commands_fill
int		t_commands_fill(t_command *c, t_mini *m);
int		allocate_full_cmd(t_command *c, t_mini *m);
int		token_indentify(char *tkn, int code, t_command *c, t_mini *m);
int		assign_redirection(char *tkn, int code, int cmd_index, t_mini *m);
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

//utilities
int		m_strlen(char **str);
char	*ft_strstr(char *hay, char *ndle);
char	*ft_strndup(const char *str, int n);
size_t	m_len(const char *s);

// execution
char	*get_path_from_env(t_mini *mini);
void	analizing_command(t_mini *mini);
void	handle_multiple_command(t_mini *mini);
void	execute_single_command(t_mini *mini);
void	handle_input_redirection(t_command *cmd, t_mini *mini);
void	handle_output_redirection(t_command *cmd, t_mini *mini);
void	execute_command(t_command *cmd, t_mini *mini);
void	c(t_command *cmd, int prev_fd, int pipes[2], t_mini *mini);
void	run_command(t_command *cmd, t_mini *mini);
void	helper_one_command(t_command *cmd, t_mini *mini);
void	s(t_command *cmd, int prev_fd, int pipes[2], t_mini *mini);
void	handle_pipe_input(int prev_fd, t_mini *mini);
void	handle_pipe_output(t_command *cmd, int pipes[2], t_mini *mini);
void	handle_output_redirectionn(t_command *cmd, t_mini *mini);
void	handle_input_redirectionn(t_command *cmd, t_mini *mini);

//builtin
int		builtin(t_mini *mini);
int		builtin_cd(t_command *cmd, t_mini *mini);
int		echo(t_command *cmd, int outfile);
int		env(t_mini *mini, int outfile);
int		export_var(const char *arg, int outfile, t_mini *mini);
int		built_pwd(int outfile, t_mini *mini);
char	*get_env(char **envp, char *name);
int		unset(t_command *cmd, t_mini *mini);
int		exit_builtin(t_command *cmd, t_mini *mini);
int		execute_builtin_in_pipe(t_command *cmd, t_mini *mini);
int		is_builtin(char *cmd_str);
int		handle_builtin(t_mini *mini);
void	print_cd_error(char *dir);

//signals
void	handle_true(int sig);
void	handler_ctrl_quit(int sig);
void	handler_false(int sig);
void	init_signals(int flag);

//errors
void	m_error_alt(char c, t_mini *m);
void	m_err(char *str, int code, t_mini *m);
void	m_error_env(char *str, t_mini *m);
void	m_exit(char *str, t_mini *m);
void	m_exit_modified(char *str, t_mini *m);

//free_memory_aux
void	m_free(char **ptr);

//free_memory
void	free_lexer_parser(t_mini *m);
void	free_lexer_parser_aux(t_mini *m);
void	free_tcommand(t_mini *m);
void	free_tcommand_aux(int i, t_mini *m);
void	free_tmini(t_mini *m);

//main
int		main(int argc, char **argv, char **envp);
int		manage_input(t_mini *m);
void	superprinter(t_mini *m);

#endif
