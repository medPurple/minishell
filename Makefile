# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 09:59:07 by ml                #+#    #+#              #
#    Updated: 2023/05/11 09:24:41 by mvautrot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

cc = cc

CFLAGS = -Wall -Wextra -Werror -g3

PATH_SRC = src

PATH_LIB = libft

SRC =   $(PATH_SRC)/env/env.c\
		$(PATH_SRC)/env/export.c\
		$(PATH_SRC)/env/lst_create.c\
		$(PATH_SRC)/parsing/parsing.c\
		$(PATH_SRC)/parsing/is_a_fct.c\
		$(PATH_SRC)/parsing/is_a_metacharacters.c\
		$(PATH_SRC)/main.c\

LIB = $(PATH_LIB)/libft.a

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(LIB) $(NAME) run

run: minishell
		@./minishell

$(NAME) : $(OBJ)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) -lreadline
	@echo "\n MINISHELL - [COMPILATION DONE]\n\n"
	clear
	@echo "\oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/"
	@echo "\ MM      MM  NN  NNNN    NN  NN   NNNNN  NN  NN  NNNNNN  NN      NN     /"
	@echo "\ MMMM  MMMM  NN  NN NN   NN  NN  NN      NN  NN  NN      NN      NN     /"
	@echo "\ MM  MM  MM  NN  NN  NN  NN  NN   NNNN   NNNNNN  NNNN    NN      NN     /"
	@echo "\ MM      MM  NN  NN   NN NN  NN      NN  NN  NN  NN      NN      NN     /"
	@echo "\ MM      MM  NN  NN    NNNN  NN  NNNNN   NN  NN  NNNNNN  NNNNNN  NNNNNN /"
	@echo "\oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/\n"


.c.o :
	@ $(CC) $(CFLAGS) -c $< -o $@

$(LIB) :
	@make -s -C $(PATH_LIB)

clean :
	@make -s -C $(PATH_LIB) clean
	@rm -f $(OBJ)

fclean : clean
	@make -s -C $(PATH_LIB) fclean
	@rm -f $(NAME)
	@echo "\n MINISHELL - [REMOVING DONE]\n"


re : fclean all

.PHONY : all clean fclean re
