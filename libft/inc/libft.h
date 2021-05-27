/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:33:17 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/27 15:12:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_main t_main;

typedef enum	e_type
{
	TYPE_SIZE_T,
	TYPE_INT,
	TYPE_LONG,
	TYPE_CHAR
}				t_e_type;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_gnl_data
{
	char	buf[BUFFER_SIZE + 1];
	int		i;
	int		n;
	int		fd;
}				t_gnl_data;

/*
**	chain list
*/
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstdel_content(t_list *lst, void *content);

/*
**	checker
*/
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
char			ft_isduplicate(long *lst, int size);
int				ft_isprint(int c);

/*
**	conversion
*/
int				ft_atoi(const char *nptr);
long			ft_atoi_l(const char *nptr);
char			*ft_itoa(int n);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
**	gnl
*/
int				get_next_line(int fd, char **line);

/*
**	memory
*/
void			ft_bzero(void *s, size_t n);
void			*calloc_secure(t_list **malloc_lst, size_t size, \
					void (*quit)(char *, t_main *), t_main *main);
void			*ft_calloc_lst(t_list **malloc_lst, size_t nbr, size_t size);
void			*ft_calloc(size_t nbr, size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memadd(void *src, size_t old, size_t new, size_t space);
void			ft_switch(void *v1, void *v2);
void			ft_freedoublestr(char ***src);

/*
**	print
*/
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);

/*
**	strings
*/
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(t_list **malloc, const char *s1);
char			*strdup_secure(t_list **malloc, const char *s1, \
					void (*quit)(char *, t_main *), t_main *main);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_doublestrlen(char **s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr (const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

/*
**	math
*/
void			ft_sort_ascending(long *lst, unsigned int size);
long			ft_median(long *tabl, unsigned int size);

/*
**	len
*/
size_t			ft_doublelen(const void **s);

#endif
