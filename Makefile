# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eli <eli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:28:09 by eli               #+#    #+#              #
#    Updated: 2023/01/06 21:17:14 by eli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================ TARGETS =======================

NAME	= computor

CC		= c++
CFLAGS	= -Wall -Werror -Wextra -g -std=c++11
INC		= -I./incs/types -I./incs/tools -I./incs/polynomial

SRCS	= rational.cpp \
			complex.cpp \
			matrix.cpp \
			function.cpp \
			main.cpp

OBJS	= $(SRCS:.cpp=.o)

SRC		= $(addprefix src/, $(SRCS))
OBJ		= $(addprefix obj/, $(OBJS))

ifdef debug
	CFLAGS += -DDEBUG=1
endif

# ================= RULES ========================

.PHONY: all
all: obj $(NAME)

obj:
	mkdir obj

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf obj

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
