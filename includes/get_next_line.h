/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:29:22 by Gecko             #+#    #+#             */
/*   Updated: 2023/10/29 11:29:25 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*read_from_fd(int fd, char **remains, char *tmp, ssize_t *read_len);
char	*get_line_and_clean_remains(char **remains);
void	*gnl_ft_bzero(void *s, size_t n);
size_t	found_newline(char *s);
char	*ft_strjoin_s1_on_the_heap(char *s1, char *s2);
size_t	gnl_ft_strlcat(char *dst, const char *src, size_t size);
char	*gnl_ft_substr(char *s, size_t start, size_t len);
char	*gnl_ft_strdup(const char *s);
size_t	gnl_ft_strlen(const char *s);

#endif
