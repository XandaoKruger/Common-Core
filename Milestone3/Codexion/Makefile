NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
DEPFLAGS = -MMD -MP
INC = -I include

SRCS =	src/cleanup.c src/coder.c src/dongle.c src/heap_utils.c \
		src/heap.c src/init.c src/log.c src/main.c src/monitor.c \
		src/parse.c src/time.c

OBJ_DIR = obj
OBJS = ${SRCS:src/%.c=${OBJ_DIR}/%.o}
DEP = ${OBJS:.o=.d}

ARGS ?= 5 800 200 200 200 3 0 fifo

all:${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "\033[0;32m✓ Compiling files \033[0m"

${OBJ_DIR}/%.o: src/%.c | ${OBJ_DIR}
	@${CC} ${CFLAGS} ${DEPFLAGS} ${INC} -c $< -o $@

${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}

clean:
	@echo "\033[0;31mRemoving objects\033[0m"
	@rm -rf ${OBJ_DIR}

fclean: clean

	@rm -f ${NAME} ${NAME}_tsan

re:

	@${MAKE} fclean
	@${MAKE} all

norm:

	@norminette src include

val: ${NAME}

	valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./${NAME} ${ARGS}

hel: ${NAME}

	valgrind --tool=helgrind ./${NAME} ${ARGS}

tsan:

	@${CC} ${CFLAGS} -fsanitize=thread ${INC} ${SRCS} -o ${NAME}_tsan
	./${NAME}_tsan ${ARGS}

-include ${DEP}

.PHONY: all clean fclean re norm val hel tsan
