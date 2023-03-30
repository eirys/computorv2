# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eli <eli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:28:09 by eli               #+#    #+#              #
#    Updated: 2023/03/30 15:23:08 by eli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                    TARGETS                                   #
# ============================================================================ #

NAME	= computorv2

CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++11 -g
INC		= -I./incs/types -I./incs/tools -I./incs/tree -I./incs/parser

SRCS	= rational.cpp \
			complex.cpp \
			matrix.cpp \
			function.cpp \
			itype.cpp \
			tokenizer.cpp \
			parser.cpp \
			computor.cpp \
			indeterminates.cpp \
			solver.cpp \
			menu.cpp \
			main.cpp

OBJS	= $(SRCS:.cpp=.o)
OBJ		= $(addprefix obj/, $(OBJS))

ifdef debug
	CFLAGS	+= -D__DEBUG=1
endif

ifdef verbose
	CFLAGS	+= -D__VERBOSE=1
endif

# ============================================================================ #
#                                     RULES                                    #
# ============================================================================ #

.PHONY: all
all: obj $(NAME)

obj:
	mkdir obj

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: debug
debug: fclean
	make debug=1

.PHONY: verbose
verbose: fclean
	make verbose=1
	

.PHONY: clean
clean:
	rm -rf obj

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
