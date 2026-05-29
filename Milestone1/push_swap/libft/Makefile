# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/17 14:14:08 by acano-kr          #+#    #+#              #
#    Updated: 2026/04/17 14:14:08 by acano-kr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
AR = ar rcs
OBJS = ${SRCS:.c=.o}

# Parte I LIBFT (LibC Functions)
SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_tolower.c ft_toupper.c

# Parte II LIBFT (Additional functions)
SRCS += ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_striteri.c ft_strjoin.c ft_strmapi.c \
		ft_strtrim.c ft_substr.c

# Parte III LIBFT (Linked Lists)
SRCS += ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

# FT_PRINTF
SRCS += ft_printf.c ft_printf_utils.c

# GET_NEXT_LINE
SRCS += get_next_line.c 

all: ${NAME}
	@echo "\033[0;32m✓ Compilando arquivos do LIBFT\033[0m"
	@echo " "
	@rm -f ${OBJS}

${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all
	@echo "\033[0;32mRecompilando LIBFT...\033[0m"
	@echo "\033[0;31m🗑️ Limpando objetos...\033[0m"
	@rm -f ${OBJS}
	@echo "\033[0;32mRecompilado com sucesso!\033[0m"

.PHONY: all fclean clean re