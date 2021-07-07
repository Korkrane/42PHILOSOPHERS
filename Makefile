# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 15:07:09 by bahaas            #+#    #+#              #
#    Updated: 2021/07/07 15:27:49 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO_NAME	= philo

SRCS 		=	srcs/main.c \
				srcs/init.c \
				srcs/free.c \
				srcs/monitoring.c \
				srcs/utils.c \
				srcs/message.c \
				srcs/actions.c \
				srcs/libft_utils.c \
				srcs/libft_utils_2.c
	
CC			= clang

CFLAGS		= -Wextra -Werror -Wall -g
#CFLAGS		=  -g -fsanitize=thread

HEADER		= -I /includes

OBJS		= ${SRCS:.c=.o}

.c.o:
	@printf "\033[34m[PHILO]\033[0m Generating .o files: \033[32mOK\033[0m%-33.33s\r\033[0m"
			@${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all: 		philo

philo: 	${OBJS}
			@printf "\n"
			@${CC} ${CFLAGS} ${HEADER} ${OBJS} -o ${PHILO_NAME} -pthread
			@echo "\033[34m[PHILO]\033[0m Building philo program : \033[32mOK\033[0m"

clean:
			@rm -rf ${OBJS}
			@echo "\033[34m[PHILO]\033[0m Delete .o files : \033[32mOK\033[0m"

fclean:		clean
			@rm -rf ${PHILO_NAME}
			@echo "\033[34m[PHILO]\033[0m Delete executable files : \033[32mOK\033[0m"

re: 		fclean all

.PHONY:	all clean fclean re philo
