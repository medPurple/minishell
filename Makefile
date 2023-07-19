# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 09:59:07 by ml                #+#    #+#              #
#    Updated: 2023/07/18 17:00:10 by wmessmer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

cc = cc

CFLAGS = -Wall -Wextra -Werror -g3

PATH_SRC = src

PATH_LIB = libft

SRC =   $(PATH_SRC)/env/env.c\
		$(PATH_SRC)/env/lst_create.c\
		$(PATH_SRC)/main.c\
		$(PATH_SRC)/parsing/parse.c\
		$(PATH_SRC)/parsing/is_a_fct.c\
		$(PATH_SRC)/parsing/meta.c\
		$(PATH_SRC)/parsing/string.c\
		$(PATH_SRC)/parsing/expand.c\
		$(PATH_SRC)/parsing/expand_exec.c\
		$(PATH_SRC)/parsing/parentheses.c\
		$(PATH_SRC)/parsing/quotes.c\
		$(PATH_SRC)/parsing/wildcard/wildcard.c\
		$(PATH_SRC)/parsing/wildcard/wildcard_utils.c\
		$(PATH_SRC)/parsing/wildcard/wildcard_replace.c\
		$(PATH_SRC)/parsing/norme/expand.c\
		$(PATH_SRC)/parsing/norme/parse.c\
		$(PATH_SRC)/parsing/norme/quotes.c\
		$(PATH_SRC)/parsing/norme/string.c\
		$(PATH_SRC)/parsing/norme/wildcard.c\
		$(PATH_SRC)/signals/signals.c\
		$(PATH_SRC)/execution/execution.c\
		$(PATH_SRC)/execution/get_status.c\
		$(PATH_SRC)/execution/minisplit.c\
		$(PATH_SRC)/execution/minisplit_bis.c\
		$(PATH_SRC)/execution/utils.c\
		$(PATH_SRC)/execution/meta.c\
		$(PATH_SRC)/execution/analyze_error.c\
		$(PATH_SRC)/execution/exec_buildin.c\
		$(PATH_SRC)/execution/cmd_redir_malloc.c\
		$(PATH_SRC)/execution/execution_choice.c\
		$(PATH_SRC)/execution/redirection/pipe.c\
		$(PATH_SRC)/execution/redirection/pipe_utils.c\
		$(PATH_SRC)/execution/redirection/exec_redir.c\
		$(PATH_SRC)/execution/redirection/open_file.c\
		$(PATH_SRC)/execution/redirection/count_redir.c\
		$(PATH_SRC)/execution/redirection/redir_utils.c\
		$(PATH_SRC)/execution/redirection/lst_create_redir.c\
		$(PATH_SRC)/execution/redirection/here_doc.c\
    	$(PATH_SRC)/execution/parentheses/parentheses.c\
		$(PATH_SRC)/buildin/echo.c\
		$(PATH_SRC)/buildin/exit.c\
		$(PATH_SRC)/buildin/pwd.c\
		$(PATH_SRC)/buildin/cd.c\
		$(PATH_SRC)/buildin/env.c\
		$(PATH_SRC)/buildin/export.c\
		$(PATH_SRC)/buildin/unset.c\
		$(PATH_SRC)/buildin/norme/cd.c\
		$(PATH_SRC)/error/error.c\




LIB = $(PATH_LIB)/libft.a

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(LIB) $(NAME) run

run: minishell
		@./minishell

runi: minishell
		@env -i ./minishell

runv : minishell
		@valgrind --suppressions=.ignore --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./minishell

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

nl : $(LIB) $(NAME)

i : $(LIB) $(NAME) runi

clean :
	@make -s -C $(PATH_LIB) clean
	@rm -f $(OBJ)

fclean : clean
	@make -s -C $(PATH_LIB) fclean
	@rm -f $(NAME)
	@echo "\n MINISHELL - [REMOVING DONE]\n"


re : fclean all

.PHONY : all clean fclean re
