# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 09:59:07 by ml                #+#    #+#              #
#    Updated: 2023/06/23 15:44:47 by mvautrot         ###   ########.fr        #
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
		$(PATH_SRC)/main.c\
		print_the_tree.c \
		$(PATH_SRC)/parsing/parse.c\
		$(PATH_SRC)/parsing/is_a_fct.c\
		$(PATH_SRC)/parsing/meta.c\
		$(PATH_SRC)/parsing/string.c\
		$(PATH_SRC)/parsing/expand.c\
		$(PATH_SRC)/parsing/parentheses.c\
		$(PATH_SRC)/parsing/quotes.c\
		$(PATH_SRC)/signals/signals.c\
		$(PATH_SRC)/execution/execution.c\
		$(PATH_SRC)/execution/minisplit.c\
		$(PATH_SRC)/execution/utils.c\
		$(PATH_SRC)/execution/meta.c\
		$(PATH_SRC)/execution/exec_malloc.c\
		$(PATH_SRC)/execution/pipe.c\
		$(PATH_SRC)/execution/execution_choice.c\
		$(PATH_SRC)/execution/redirection/exec_redir_right.c\
		$(PATH_SRC)/execution/redirection/exec_redir_left.c\
		$(PATH_SRC)/execution/redirection/exec_utils.c\
		$(PATH_SRC)/execution/redirection/lst_create_redir.c\
		$(PATH_SRC)/execution/redirection/here_doc.c\
		$(PATH_SRC)/buildin/echo.c\
		$(PATH_SRC)/buildin/exit.c\
		$(PATH_SRC)/buildin/pwd.c\
		$(PATH_SRC)/buildin/cd.c\




LIB = $(PATH_LIB)/libft.a

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(LIB) $(NAME) run

run: minishell
		@./minishell

runv : minishell
		@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

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

v :$(LIB) $(NAME) runv

clean :
	@make -s -C $(PATH_LIB) clean
	@rm -f $(OBJ)

fclean : clean
	@make -s -C $(PATH_LIB) fclean
	@rm -f $(NAME)
	@echo "\n MINISHELL - [REMOVING DONE]\n"


re : fclean all

.PHONY : all clean fclean re
