# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/04 23:54:53 by Etienne           #+#    #+#              #
#    Updated: 2017/07/04 23:54:55 by Etienne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FLAGS= -Wall -Werror -Wextra -O0 -g -fsanitize=address


SRC= main.c\
	parsing.c\
	display.c\
	display_dir.c\
	display_file.c\
	display_l.c\
	tools_dir.c\
	tools_file.c\
	tools_display.c\

NAME = ft_ls
CC = gcc
OBJ = $(SRC:.c=.o)
RM = rm -rf
INC = -I includes/
FT = -L libft/ -lft
CG = \033[92m
CY =  \033[93m
CE = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[K$(CY)[FT_LS] :$(CE) $(CG)Creating Library$(CE)\033[1A";
	@make -C libft/ fclean
	@make -C libft/
	@$(CC)  $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(FT)
	@echo "\033[K$(CY)[FT_LS] :$(CE) $(CG)Compiled FT_LS$(CE)";

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "\033[K$(CY)[FT_LS] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:
	@$(RM) $(OBJ)
	@echo "\033[K$(CY)[FT_LS] :$(CE) $(CG)Cleaning Object files $(CE)";

fclean: clean
	@$(RM) $(NAME)
	@make -C libft/ fclean
	@echo "\033[K$(CY)[FT_LS] :$(CE) $(CG)Cleaning FT_LS $(CE)";

re: fclean all

.PHONY : all clean fclean re

