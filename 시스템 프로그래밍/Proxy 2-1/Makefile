NAME = proxy_cache

CC = gcc

CFLAGS = -lcrypto

SRCS = ./proxy_cache.c ./check_url.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

${NAME} : ${OBJS}
	${CC} $^ -o $@ ${CFLAGS}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${NAME}

re : fclean all

.PHONY: all	clean	fclean	re