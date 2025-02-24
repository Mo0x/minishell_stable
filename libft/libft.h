/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:54:12 by Gecko             #+#    #+#             */
/*   Updated: 2023/08/06 17:54:09 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

# define INT_TYPE 66666
# define STR_TYPE 77777
# define OTH_TYPE 88888
# define VOID_TYPE 99999
# define SUCCESS 1
# define FAILURE 0
# define ALLOC 10
# define FREE 11
# define CLEAR 12
# define PRINT_SIZE 13
# define INIT_ALLOC 14
# define CRITICAL 1
# define SAFE 0

typedef union u_data
{
	int		int_val;
	char	*str_val;
	char	*str_util;
	void	*oth_val;
	char	*infos;
}	t_data;

typedef struct s_ptr_lst
{
	int					is_critical;
	void				*ptr;
	struct s_ptr_lst	*next;
	struct s_ptr_lst	*prev;
}	t_ptr_lst;

typedef enum e_lst_nodetype
{
	LSTCMD,
	LSTCMDARG,
	LSTREDIR,
	LSTLIMITER,
	LSTFILE,
	LSTVOID,
	LSTEMPTY
}	t_lst_nodetype;

typedef struct s_list
{
	int				data_type;
	t_data			content;
	int				is_heredoc_next;
	int				index;
	int				depth;
	int				par_group_index;
	int				is_bridge;
	t_lst_nodetype	nodetype;
	struct s_list	*next;
}	t_list;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size, int is_critical);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1, int is_critical);
char		*ft_saferdup(const char *s, int is_critical);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strjoin(char const *s1, char const *s2, int is_critical);
char		**ft_split(char const *s, char c, int is_critical);
char		**ft_split_charset(char const *s, char *set, int is_critical);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_substr(char const *s, unsigned int start, \
							size_t len, int is_critical);
char		*ft_strtrim(char const *s1, char const *s2, int is_critical);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char), \
										int is_critical);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_lstadd_back(t_list **lst, t_list *n);
void		ft_lstadd_front(t_list **lst, t_list *n);
int			ft_lstadd_after(t_list **lst, t_list *toadd, t_list *position);
void		ft_lstadd_before(t_list **lst, t_list *target, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content, int type, int is_critical);
t_list		*ft_split_lst(char *content, int sep, int is_critical);
void		ft_lstdelone(t_list **lst, t_list *node_to_delete);
t_list		*replace_node(t_list *head, t_list *to_replace, t_list *new_node);
int			ft_lstsize(t_list *lst);
int			ft_strcmp(char *s1, char *s2);

//ALLOCATOR
void		*allocator(int size, int type, void *ptr, int is_critical);
void		*walloc(int size, int is_critical);
void		wfree(void *ptr);
void		wclear(int free_critical);

t_ptr_lst	*ptrlst_new(void *ptr, int is_critical);
void		ptrlst_addfront(t_ptr_lst **h, t_ptr_lst *n);
void		ptrlst_clear(t_ptr_lst **h, int is_critical);
int			ptrlst_size(t_ptr_lst *h);
void		ptrlst_addfront(t_ptr_lst **h, t_ptr_lst *n);
int			ptrlst_size(t_ptr_lst *h);
void		ptrlst_delone(t_ptr_lst **h, void *ptr);

int			ft_tabtablen(char **tab);

int			ft_strsuffix(char *s, char *pattern);
int			ft_strprefix(char *s, char *pattern);
char		*ft_strtolower(char *s);
void		ft_sorttabtab(char ***array, int rows, int cols);
int			ft_tabtabheigth(char **tab);

int			ft_abs(int x);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strncat(char *dest, const char *src, size_t n);
int			is_blank(char c);
int			has_blank(char *s);
#endif
