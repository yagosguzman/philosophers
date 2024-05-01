# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:05:57 by ysanchez          #+#    #+#              #
#    Updated: 2024/04/30 21:36:25 by ysanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
FLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread #-fsanitize=address
RM = rm -rf
HEADER = philo.h
SRC = main.c error_handler.c check_arg.c utils.c data_init.c instructions.c \
		get_set_mutex.c dining.c
OBJ = $(patsubst %.c, temp/%.o, $(SRC))
DEPS = $(addprefix temp/,$(addsuffix .d, $(basename $(SRC))))

all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
	@echo "Executable ready!"

temp/%.o: %.c Makefile | temp
	@$(CC) $(FLAGS) -c $< -o $@

temp:
	@mkdir -p temp

clean:
	@$(RM) $(OBJ)
	@$(RM) $(DEPS)
	@$(RM) temp
	@echo "Objects and libraries successfully removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "Executable successfully removed"

re: fclean all

.PHONY: make all clean fclean re bonus


