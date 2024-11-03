# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 16:19:45 by dangonz3          #+#    #+#              #
#    Updated: 2024/11/03 14:20:55 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

#colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

#
SRC_DIR = sources
SRC_FILES = /execution/one_command.c /execution/multiple_commad.c /execution/execution.c \
/builtin/unset.c /builtin/pwd.c /builtin/export.c /builtin/exit.c /builtin/env.c /builtin/echo.c /builtin/cd.c /builtin/builtin.c \
/parser/check_commands.c /parser/delete_quotes.c /parser/envp_aux.c /parser/expand_vars.c /parser/getprompt.c /parser/here_doc.c /parser/init_struct.c /parser/lexer.c /parser/open_files.c /parser/others.c /parser/parser.c  /parser/pre_check_commands.c /parser/t_commands_fill.c /parser/t_commands.c /parser/token_check.c\
/errors.c /free_memory.c /main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)

#headers
INCLUDE = -I./includes/
FLAGS = -lreadline -lncurses

#LIBFT
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
	
#program
all: $(LIBFT_LIB) $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(INCLUDE) $(FLAGS)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) all -s
	
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"

#additional

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean: 
	rm -f $(OBJ)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

.PHONY:	all clean fclean re
