NAME = libft.a

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

# sources
SRC_FILES = ft_split ft_striteri ft_strmapi ft_atoi ft_bzero \
ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit \
ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy \
ft_memmove ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_dprintf \
ft_putstr_fd ft_strchr ft_strcmp ft_strdup ft_strjoin ft_strlcat \
ft_strlcpy ft_strlen ft_strncmp ft_strnstr ft_strrchr \
ft_strtrim ft_substr ft_tolower ft_toupper ft_lstmap_bonus \
ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus \
ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_printf ptf_auxiliars \
ptf_printer get_next_line get_next_line_utils get_next_line_bonus get_next_line_utils_bonus
SRC = $(addsuffix .c, $(SRC_FILES))
OBJS = $(SRC:.c=.o)

# colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

#program
all: $(NAME)
	@echo "$(COLOR_GREEN)------------ MESSAGE: LIBFT COMPILED ------------ $(COLOR_RESET)"

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

#additional functions
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
