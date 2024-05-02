# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:05:57 by ysanchez          #+#    #+#              #
#    Updated: 2024/05/02 22:41:16 by ysanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf
HEADER = philo.h
SRC = main.c error_handler.c parser.c utils.c data_init.c instructions.c \
		checkers.c dining.c
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


