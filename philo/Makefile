SRCS = philo_main.c parsing.c initialization.c ft_sleep.c \
	termination.c monitoring_utils.c forks_utils.c monitor_thread.c parsing_2.c
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ../libft/libft.a

all: philo

${LIBFT}:
	cd ../libft && make

%.o: %.c philo_header.h
	${CC} ${CFLAGS} -c $< -o $@

philo: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o philo

re: fclean all

clean:
	rm -f ${OBJS}
	cd ../libft && make clean

fclean: clean
	rm -f philo
	cd ../libft && make fclean

.PHONY: clean fclean all
