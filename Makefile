SRCS = philo/philo_main.c philo/parsing.c philo/initialization.c philo/ft_sleep.c \
	philo/termination.c philo/monitoring_utils.c
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: philo/philo

${LIBFT}:
	cd libft && make

%.o: %.c philo/philo_header.h
	${CC} ${CFLAGS} -c $< -o $@

philo/philo: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o philo/philo

clean:
	rm -f ${OBJS}
	cd libft && make clean

fclean: clean
	rm -f philo/philo
	cd libft && make fclean
