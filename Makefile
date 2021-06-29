# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 15:07:09 by bahaas            #+#    #+#              #
#    Updated: 2021/06/29 15:34:53 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO_NAME	= philo

SRCS 		=	srcs/main.c \
				srcs/init.c \
				srcs/actions.c \
				srcs/utils.c
	
CC			= clang

#CFLAGS		= -Wextra -Werror -Wall -g
CFLAGS		=  -g

HEADER		= -I /includes

OBJS		= ${SRCS:.c=.o}

.c.o:
	@printf "\033[34m[PHILO]\033[0m Generating .o files: \033[32mOK\033[0m%-33.33s\r\033[0m"
			@${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all: 		philo

philo: 	${OBJS}
			@printf "\n"
			@make -C libft/ --no-print-directory -s
			@${CC} ${CFLAGS} ${HEADER} ${OBJS} -o ${PHILO_NAME} -L libft/ -lft -pthread
			@echo "\033[34m[PHILO]\033[0m Building philo program : \033[32mOK\033[0m"

clean:
			@make clean -C libft/ --no-print-directory
			@rm -rf ${OBJS}
			@echo "\033[34m[PHILO]\033[0m Delete .o files : \033[32mOK\033[0m"

fclean:		clean
			@make fclean -C libft/ --no-print-directory
			@rm -rf ${PHILO_NAME}
			@echo "\033[34m[PHILO]\033[0m Delete executable files : \033[32mOK\033[0m"

re: 		fclean all

.PHONY:	all clean fclean re philo
