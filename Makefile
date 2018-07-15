#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/30 18:43:03 by ahrytsen          #+#    #+#              #
#    Updated: 2018/07/15 13:43:28 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	taskmaster

NAME_C		=	taskmasterctl
NAME_D		=	taskmasterd

DIRSRC		=	./src/
DIRSRC_C	=	./src/client/
DIRSRC_D	=	./src/daemon/

DIROBJ		=	./obj/
DIROBJ_C	=	./obj/client/
DIROBJ_D	=	./obj/daemon/

INCLUDE_C	=	-I./inc/ -I./libft/includes
INCLUDE_D	=	-I./inc/ -I./libft/includes -I ~/.brew/include

INC_LIB_C	=	-L./libft -lftprintf -ltermcap
INC_LIB_D	=	-L./libft -lftprintf -L ~/.brew/lib/ -lyaml

SUB_MAKE	=	./libft/
SUB_OBJ		=	libftprintf.a
LIBFT		=	libft/libftprintf.a

SRC			=	exchange.c

SRC_C		=	main.c\
				\
				ft_readline/ft_autocomplit.c\
				ft_readline/ft_readline.c\
				ft_readline/ft_readline_action.c\
				ft_readline/line.c\
				ft_readline/rl_init.c\
				ft_readline/ft_cursor.c\
				ft_readline/ft_readline_helper.c\
				ft_readline/ft_history.c\
				ft_readline/ft_highlight.c\
				ft_readline/line_edit.c\
				ft_readline/ft_prompt.c\
				ft_readline/ft_read.c

SRC_D		=	main.c\
				d_flags.c\
				d_init.c\
				commands.c\
				parse_config_tree.c\
				record_config.c\
				record_config_proc.c\
				free_config_tree.c\
				check_config.c\
				debug.c\
				d_status.c\
				d_start.c\
				d_stop.c\
				proc_utils.c\
				service_routines.c

HDR_C		=	inc/ft_readline.h
HDR_D		=	inc/daemon.h

OBJ			=	$(addprefix $(DIROBJ), $(SRC:.c=.o))
OBJ_C		=	$(addprefix $(DIROBJ_C), $(SRC_C:.c=.o))
OBJ_D		=	$(addprefix $(DIROBJ_D), $(SRC_D:.c=.o))

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	gcc
RM			=	rm -rf
ECHO		=	echo

all		:		$(NAME)

$(NAME)	:		$(NAME_C) $(NAME_D)

$(NAME_C):		$(DIROBJ_C) $(OBJ) $(OBJ_C) $(LIBFT)
				@$(CC) $(INCLUDE_C) $(INC_LIB_C) $(CFLAGS) -o $(NAME_C) $(OBJ_C) $(OBJ)
				@$(ECHO) "\033[31m> \033[32m"$(NAME_C)": Compiled\033[0m"

$(NAME_D):		$(DIROBJ_D) $(OBJ) $(OBJ_D) $(LIBFT)
				@$(CC) $(INCLUDE_D) $(INC_LIB_D) $(CFLAGS) -o $(NAME_D) $(OBJ_D) $(OBJ)
				@$(ECHO) "\033[31m> \033[32m"$(NAME_D)": Compiled\033[0m"

lib		:
				@$(MAKE) -C $(SUB_MAKE) -j3

$(LIBFT):		lib

clean	:
				@($(RM) $(DIROBJ))
				@$(ECHO) "\033[31m> \033[33m"$(NAME)": Directory cleaned\033[0m"
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) clean
endif

clean_c	:
				@($(RM) $(DIROBJ_C))
				@$(ECHO) "\033[31m> \033[33m"$(NAME_C)": Directory cleaned\033[0m"

clean_d	:
				@($(RM) $(DIROBJ_D))
				@$(ECHO) "\033[31m> \033[33m"$(NAME_D)": Directory cleaned\033[0m"

fclean	:		fclean_c fclean_d
				@($(RM) $(DIROBJ))
				@$(ECHO) "\033[31m> \033[33m"$(NAME)": Directory cleaned\033[0m"
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) fclean
endif

fclean_c	:	clean_c
				@$(ECHO) "\033[31m> \033[33m"$(NAME_C)": Remove executable\033[0m"
				-@$(RM) $(NAME_C)

fclean_d	:	clean_d
				@$(ECHO) "\033[31m> \033[33m"$(NAME_D)": Remove executable\033[0m"
				-@$(RM) $(NAME_D)

re		:		fclean all

re_c		:		fclean_c $(NAME_C)

re_d		:		fclean_d $(NAME_D)

.PHONY	:		all clean re

$(DIROBJ):
				@mkdir -p $(DIROBJ)

$(DIROBJ_C):	$(DIROBJ)
				@mkdir -p $(DIROBJ_C)
				@mkdir -p $(DIROBJ_C)/ft_readline

$(DIROBJ_D):	$(DIROBJ)
				@mkdir -p $(DIROBJ_D)

$(OBJ):			$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR_D)
				@$(CC) $(INCLUDE_D) $(CFLAGS) -o $@ -c $<

$(OBJ_C):		$(DIROBJ_C)%.o : $(DIRSRC_C)%.c $(HDR_C)
				@$(CC) $(INCLUDE_C) $(CFLAGS) -o $@ -c $<

$(OBJ_D):		$(DIROBJ_D)%.o : $(DIRSRC_D)%.c $(HDR_D)
				@$(CC) $(INCLUDE_D) $(CFLAGS) -o $@ -c $<
