# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amulin <amulin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/06 11:02:43 by amulin            #+#    #+#              #
#    Updated: 2016/08/24 16:20:32 by amulin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS_NAME = $(shell uname -s)
ifeq ($(OS_NAME),Linux)
	CC = gcc
endif
ifeq ($(OS_NAME),Darwin)
	CC = clang
endif


NAME = minishell

UIALIGN = \r\t\t

UICEPTION = \033[0m─ $(NAME)\033[0m$(UIALIGN)

UIWAIT = $(UIALIGN)[\033[33m \xE2\x8C\x9B \033[0m]

UIOK = $(UIALIGN)[\033[32m \xE2\x9C\x94 \033[0m]

UIINFO = $(UIALIGN)[\033[36m i \033[0m]

FLAGS = -Wall -Werror -Wextra

ifeq ($(CC),gcc)
	FLAGS += -std=gnu99
endif

SRCS = main.c msh_parsing.c msh_process.c msh_exec.c msh_prompt.c\
	   msh_env.c msh_errormgt.c msh_debug.c libft_addition.c

SRCDIR = sources/

SOURCES = $(addprefix $(SRCDIR), $(SRCS))

INCLUDES = minishell.h

INCLUDIR = includes/

HEADERS = $(addprefix $(INCLUDIR), $(INCLUDES))

LFT = libft.a

LFT_REAL = libft_all.a

LFTDIR = libft/

LIBFT = $(addprefix $(LFTDIR), $(LFT))

LIBFT_REAL = $(addprefix $(LFTDIR), $(LFT_REAL))

LFTINCLUDIR = $(addprefix $(LFTDIR), includes/)

.PHONY: all, clean, fclean, re, libft

all: libft $(NAME)
	@printf "$(UICEPTION)$(UIINFO) All fine for $(NAME)\n"
	
$(NAME): $(LIBFT_REAL) $(SOURCES) $(HEADERS)
	@printf "$(UICEPTION)$(UIWAIT) Compiling $(NAME)"
	@$(CC) $(FLAGS) $(SOURCES) -I $(INCLUDIR) -I $(LFTINCLUDIR) -L $(LFTDIR) \
		-lft -o $(NAME)
	@printf " $(UIOK)\n"

$(LIBFT_REAL): libft

libft: 
	@printf "$(UICEPTION)$(UIINFO) Calling make on libft\n"
	@make -C libft
#	@printf "$(UICEPTION)$(UIINFO) $(LFT) compiled\n"

clean:
	@printf "$(UICEPTION)$(UIINFO) Running clean\n"
	@printf "$(UICEPTION)$(UIINFO) Calling clean on libft\n"
	@make -C libft clean
	@printf "$(UICEPTION)$(UIINFO) clean completed\n"

fclean:
	@printf "$(UICEPTION)$(UIINFO) Running fclean\n"
	@printf "$(UICEPTION)$(UIWAIT) Deleting $(NAME)"
	@rm -f $(NAME)
	@printf " $(UIOK)\n"
	@printf "$(UICEPTION)$(UIINFO) Calling fclean on libft\n"
	@make -C libft fclean
	@printf "$(UICEPTION)$(UIINFO) fclean completed\n"

re: fclean all
