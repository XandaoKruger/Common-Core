NAME = push_swap
CC = cc
FLAGS = -g -Wall -Wextra -Werror -I .
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a
OBJS = ${FILES:.c=.o}

# Folders
OPER = operations
SRCS = srcs
ALGO = algorithm

#Files inside algorithm
FILES =		${ALGO}/algo_simple.c ${ALGO}/algo_medium.c \
			${ALGO}/algo_complex.c ${ALGO}/algo_utils.c \
			${ALGO}/algo_utils2.c

#Files inside operations
FILES +=	${OPER}/push_swap_operations.c ${OPER}/rotate_operations.c \
			${OPER}/reverse_operations.c ${OPER}/operation_utils.c

#Files inside srcs
FILES +=	${SRCS}/stack.c ${SRCS}/parse.c ${SRCS}/main.c ${SRCS}/bench.c\
			${SRCS}/utils.c ${SRCS}/push_swap.c ${SRCS}/flags.c

all: ${LIBFT} ${NAME}
	@echo "\033[0;32m✓ Compilando arquivos \033[0m"
	@echo " "

${LIBFT}:
	@make -C ${LIBFT_DIR}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} -L ${LIBFT_DIR} -lft -o ${NAME}

%.o: %.c
	@${CC} ${FLAGS} -I ${LIBFT_DIR} -c $< -o $@

clean:
	@make -C ${LIBFT_DIR} clean
	@rm -f ${OBJS}

fclean: clean
	@make -C ${LIBFT_DIR} fclean
	@rm -f ${NAME}

re: fclean all
	@echo "\033[0;32mRecompilando...\033[0m"
	@echo " "
	@echo "\033[0;32mRecompilado com sucesso!\033[0m"

.PHONY: all clean fclean re