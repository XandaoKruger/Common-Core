# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/28 08:02:26 by acano-kr          #+#    #+#              #
#    Updated: 2026/05/15 12:09:48 by acano-kr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
AR = ar rcs
SRCS = ft_printf.c ft_pchar.c ft_pnbr.c ft_phex.c ft_pf_utils.c

OBJS = ${SRCS:.c=.o}

all:${NAME}
	@echo "\033[0;32m✓ Compilando arquivos \033[0m"
	@echo " "
	@echo "\033[0;31m🗑️ Limpando objetos...\033[0m"
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
	@echo "\033[0;32mRecompilando...\033[0m"
	@echo " "
	@rm -f ${OBJS}
	@echo "\033[0;32m✓ Recompilado com sucesso!\033[0m"

.PHONY: all clean fclean re