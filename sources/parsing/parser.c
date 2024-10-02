/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:37:07 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/02 21:13:15 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NO_OF_ITERATORS 5

/**
 * @brief  Trys to get correct current parser token
 * @note   Helper function of get_tokens
 * @param  *lex_toks[]:
 * @param  *par_toks[]:
 * @param  *iter:
 * @retval int to indicate exit status
 */
static int	get_par_tok(char *lex_toks[], t_par_tok *par_toks[], t_iter *iter)
{
	int	tmp;

	tmp = EXIT_SUCCESS;
	tmp = get_tok_type(lex_toks[iter[lex]], iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_tok_redir(lex_toks, iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_tok_cmd(lex_toks[iter[lex]], par_toks[iter[par]], iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_special_tok(lex_toks[iter[lex]], par_toks, iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	return (EXIT_SUCCESS);
}

/**
 * @brief  Trys to create correct tokens for expander
 * @note
 * @param  *lex_toks[]: Tokens from lexer to create parser tokens from
 * @retval int to indicate exit status
 */
static int	get_tokens(char *lex_toks[])
{
	t_par_tok	**par_toks;
	t_iter		*iter;
	int			get_par_tok_exit_status;

	iter = ft_calloc(NO_OF_ITERATORS + 1, sizeof(*iter));
	if (iter == NULL)
		return (EXIT_FAILURE);
	set_iter(iter);
	par_toks = ft_calloc(get_tokens_size(lex_toks) + 1, sizeof(*par_toks));
	if (par_toks == NULL)
		return (EXIT_FAILURE);
	set_par_toks(par_toks);
	while (lex_toks[iter[lex]])
	{
		get_par_tok_exit_status = get_par_tok(lex_toks, par_toks, iter);
		if (get_par_tok_exit_status == EXIT_FAILURE)
			return (free_parser(par_toks, iter, EXIT_FAILURE));
		else if (get_par_tok_exit_status == EXIT_SYNTAX_ERROR)
			return (free_parser(par_toks, iter, EXIT_SYNTAX_ERROR));
	}
	free(iter);
	return (EXIT_SUCCESS);
}

static char	**interprete_env_vars(char *lex_toks[])
{
	int		i;

	i = 0;
	while (lex_toks[i])
	{
		lex_toks[i] = interprete_env_var(lex_toks[i]);
		if (lex_toks[i] == NULL)
			return (NULL);
		if (ft_strstr(lex_toks[i], "&&") || ft_strstr(lex_toks[i], "||"))
			break ;
		i++;
	}
	return (lex_toks);
}

int	parser(char *lexer_tokens[])
{
	t_par_tok	**tokens;
	int			exit_code;

	lexer_tokens = interprete_env_vars(lexer_tokens);
	if (lexer_tokens == NULL)
		return (EXIT_FAILURE);
	set_lex_toks(lexer_tokens);
	exit_code = get_tokens(lexer_tokens);
	if (exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (exit_code == EXIT_SYNTAX_ERROR)
		return (EXIT_SUCCESS);
	tokens = get_par_toks();
	return (free_par_toks(tokens, expander(tokens)));
}

//---------------------------------------------

int	parser(t_mini *m)
{
	int	i;

	i = 0;
	while (m->tokens[i])
		if (expand_var(i, m) == 2) //gestiona el caso "*\0". En este caso la tokens[i] tiene que expandirse de char * a char **.
	
}

typedef enum e_parser_tok_type
{
	std = 0,
	subshell = 1,
	and = 2,
	or = 3,
}	t_par_tok_type;

typedef enum e_parser_redirection_type
{
	is_pipe = 0,
	is_in = 1,
	is_in_heredoc = 2,
	is_out = 3,
	is_out_append = 4,
}	t_redir_type;

typedef struct s_parser_tok
{
	t_par_tok_type	type;
	t_redir_type	redir_type[5];
	char			**cmd;
	size_t			cmd_size;
	char			**in;
	size_t			in_size;
	char			**out;
	size_t			out_size;
}	t_par_tok;


/* 
En el contexto de un shell, "&&" y "||" son operadores lógicos:
&&: Indica que el segundo comando se debe ejecutar solo si el primero tuvo éxito (es decir, devolvió un estado de salida de 0).
||: Indica que el segundo comando se debe ejecutar solo si el primero falló (es decir, devolvió un estado de salida diferente de 0). 
*/