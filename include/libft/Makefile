# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 22:55:52 by mrazem            #+#    #+#              #
#    Updated: 2025/08/08 16:20:21 by mrazem           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall

# SRC    := $(wildcard *.c)
SRC = ft_memset.c ft_strlen.c ft_isprint.c ft_isdigit.c \
	ft_isascii.c ft_isalpha.c ft_isalnum.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlcpy.c ft_toupper.c \
	ft_tolower.c ft_strchr.c ft_strncmp.c ft_strrchr.c ft_strlcat.c \
	ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr_fd.c \
	ft_safe_write.c ft_printchar.c ft_printed.c ft_printf.c ft_printhex.c ft_printnum.c ft_printptr.c \
	ft_printstring.c ft_printunsigned.c

	
OBJ =$(SRC:.c=.o)

NAME = libft.a

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re