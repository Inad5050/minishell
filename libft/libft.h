/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:16:24 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/21 20:46:42 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

/* LIBFT */

int			ft_atoi(const char *str);
void		ft_bzero(void *ptr, size_t size);
void		*ft_calloc(size_t num_elements, size_t element_size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *ptr, int initial_value, size_t size);
char		*ft_strchr(const char *str, char character);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strnstr(const char *hay, const char *ndle, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strrchr(const char *str, int character);

/* PART 2 */

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* BONUS */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));

/* PRINT_F */

int			ft_printf(char const *s, ...);
int			ptf_selection(char const *s, int i, va_list args);

int			ptf_putnbr(int n, int count);
int			ptf_putnbr_u(unsigned int n, int count);

int			ptf_print_d(int arg, char format);
int			ptf_print_x(size_t arg, char format, int count);
int			ptf_print_s(char *arg);
int			ptf_print_c(char arg);

/* GNL */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*ft_get_next_line(int fd);
char		*gnl_excess(char *deposit);
char		*gnl_cut_line(char *deposit);
char		*gnl_strjoin(char *line, const char *buffer);

/* FT_DPRINTF*/
int	ft_dprintf(int fd, char const *s, ...);

#endif
