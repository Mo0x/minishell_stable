# **************************************************************************** #
#                                                                              #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/16 10:39:52 by Gecko             #+#    #+#              #
#    Updated: 2023/08/06 17:52:47 by Gecko            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC	=	ft_atoi.c		\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_putchar_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c		\
		ft_split_charset.c		\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_striteri.c	\
		ft_strjoin.c	\
		ft_strlcat.c 	\
		ft_strlcpy.c	\
		ft_strcpy.c	\
		ft_strlen.c 	\
		ft_strmapi.c	\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_tolower.c	\
		ft_toupper.c	\
		ft_lstdelone.c	\
		ft_lstreplace_node.c	\
		ft_lstadd_back_bonus.c	\
		ft_lstadd_front_bonus.c	\
		ft_lstlast_bonus.c		\
		ft_lstnew_bonus.c		\
		ft_split_lst.c		\
		ft_strcmp.c		\
		ft_lstadd_after.c		\
		ft_lstadd_before.c		\
		ft_lstsize_bonus.c		\
		allocator.c		\
		allocator_warpers.c \
		mlist_utils.c		\
		ft_tabtablen.c		\
		ft_tabtabheigth.c		\
		ft_affix.c		\
		ft_strtolower.c \
		ft_sorttabtab.c \
		ft_abs.c \
		ft_strstr.c \
		ft_strncat.c \
		ft_isblank.c \
		ft_lstdelone.c
		# ft_lstiter_bonus.c		\
		# ft_lstmap_bonus.c		\
		# ft_lstclear_bonus.c		\

OBJS = $(SRC:.c=.o)


BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf
AR = ar crs

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	$(RM) $(NAME)		

re:	fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS)  $(BONUS_OBJS)

.PHONY:	all clean fclean re bonus
