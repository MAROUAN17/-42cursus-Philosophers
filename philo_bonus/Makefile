SRCS_BNS = philo_main_bonus.c parsing_bonus.c termination_bonus.c \
	initialization_bonus.c ft_sleep_bonus.c monitoring_utils_bonus.c \
	parsing_2_bonus.c monitoring_thread_bonus.c function_protections_bonus.c
OBJS_BNS = ${SRCS_BNS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ../libft/libft.a
NAME = philo_bonus

all: ${NAME}

${LIBFT}:
	cd ../libft && make

%.o: %.c philo_header_bonus.h
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS_BNS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS_BNS} ${LIBFT} -o philo_bonus

re: fclean all

clean:
	rm -f ${OBJS_BNS}
	cd ../libft && make clean

fclean: clean
	rm -f philo_bonus
	cd ../libft && make fclean

.PHONY: clean fclean all bonus re