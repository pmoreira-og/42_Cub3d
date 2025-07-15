/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:31:49 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/22 16:32:46 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// STRUCTS

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// GET NEXT LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char				*get_next_line(int fd);
char				*ft_add_line_chunck(char *start, char *chunck);
void				ft_buffrealign(char *buff);
int					ft_withnewline(char *line);
int					ft_linelen(char *str);
void				*ft_buffzero(char *buff, size_t n);

// FT IS

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_iswhitespace(int c);

// FT LST

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

// FT MATRIX
void				free_matrix_until(void **matrix, int max);
void				free_matrix(void **matrix);
size_t				ft_matrixlen(char **matrix);
char				**ft_split(char const *s, char c);
char				**matrix_add_to_index(char **matrix, char *add, size_t idx,
						size_t len);
char				**matrix_add_front(char *add, char **original);
char				**matrix_dup_char(char **original_matrix);

// FT NUM
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					int_check(char *arg, int *arg_n);
int					long_check(char *arg, long *arg_n);

// FT PRINT

int					ft_printf(const char *input, ...);
int					ft_ispercent(const char *input, va_list args);
int					ft_printchar(int c);
int					ft_printstr(char *str);
int					ft_prtnb_base(long nbr, char *base, int len);
int					ft_printptr(unsigned long p, int flag);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
int					printf_fd(int fd, const char *input, ...);
int					printchar_fd(int c, int fd);
int					printstr_fd(char *str, int fd);
int					prtnb_base_fd(long nbr, char *base, int len, int fd);
int					printptr_fd(unsigned long p, int flag, int fd);

// FT STRINGS

char				*ft_strchr(const char *s, int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(const char *src);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t destsize);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(char *src, size_t n);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
char				*ft_strrchr(const char *str, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);

// FT UTILS

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *dest, int filler, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif