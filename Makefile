# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 09:59:07 by ml                #+#    #+#              #
#    Updated: 2023/04/05 14:06:36 by mvautrot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

cc = cc

CFLAGS = -Wall -Werror -Wextra -g3

PATH_SRC = src

PATH_LIB = libft

SRC =  $(PATH_SRC)/main.c\

LIB = $(PATH_LIB)/libft.a

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(LIB) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@echo "\n Compilation OK\n"

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB) :
	@make -s -C $(PATH_LIB)

clean :
	make -C $(PATH_LIB) clean
	rm -f $(OBJ)

fclean : clean
	make -C $(PATH_LIB) fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
