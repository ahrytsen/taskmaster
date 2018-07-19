#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 20:19:57 by ahrytsen          #+#    #+#              #
#    Updated: 2018/07/19 18:42:56 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= libftprintf.a

DIROBJ	= ./obj/

INCLUDE	= -I./includes/

SRC		= ft_lstpush_back.c ft_putstr.c ft_strmapi.c ft_lstpush_front.c		\
		ft_putstr_fd.c ft_strncat.c ft_atoi.c ft_lstsplit.c ft_strcat.c		\
		ft_strncmp.c ft_bzero.c ft_memalloc.c ft_strchr.c ft_strncpy.c		\
		ft_isalnum.c ft_memccpy.c ft_strclr.c ft_strnequ.c ft_isalpha.c		\
		ft_memchr.c ft_strcmp.c ft_strnew.c ft_isascii.c ft_memcmp.c		\
		ft_strcpy.c ft_strnstr.c ft_isdigit.c ft_memcpy.c ft_strdel.c		\
		ft_strrchr.c ft_isprint.c ft_memdel.c ft_strdup.c ft_strsplit.c		\
		ft_itoa.c ft_memmove.c ft_strequ.c ft_strstr.c ft_lstadd.c			\
		ft_memset.c ft_striter.c ft_strsub.c ft_lstadd_end.c ft_putchar.c	\
		ft_striteri.c ft_strtrim.c ft_lstdel.c ft_putchar_fd.c ft_strjoin.c	\
		ft_tolower.c ft_lstdelone.c ft_putendl.c ft_strlcat.c ft_toupper.c	\
		ft_lstiter.c ft_putendl_fd.c ft_strlen.c ft_lstmap.c ft_putnbr.c	\
		ft_strlen_c.c ft_lstnew.c ft_putnbr_fd.c ft_strmap.c get_next_line.c\
		ft_strextend.c ft_ultoa_base.c ft_strulen.c ft_atol.c ft_ltoa.c		\
		ft_wcharlen.c ft_dtoa.c ft_ldtoa.c ft_dtoea.c ft_ldtoea.c			\
		ft_sort_params.c ft_strdup_arr.c ft_isalnum_str.c ft_isalpha_str.c	\
		ft_isnumeric_str.c ft_isascii_str.c ft_isprint_str.c				\
		ft_iswhitespace.c ft_atoi_base.c ft_atol_base.c ft_strarr_free.c	\
		ft_strhalfextend.c  ft_arrstr.c ft_count_digits.c                   \
		\
		ft_printf/ft_printf.c ft_printf/ft_phendler.c ft_printf/ft_pbuf.c	\
		ft_printf/ft_pfloat.c ft_printf/ft_phelper.c ft_printf/ft_fatal.c	\
		ft_printf/ft_pbuf_str.c

HDR		= includes/libft.h includes/ft_printf.h

OBJ		= $(addprefix $(DIROBJ), $(SRC:.c=.o))

CC		= gcc

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -g
	endif
else
CFLAGS	= -Wall -Wextra -Werror -Ofast -flto=thin
endif

all: $(NAME)

$(NAME): $(DIROBJ) $(OBJ)
	@ar rc $(NAME) $(OBJ);
	@ranlib $(NAME);
	@echo "\033[31m> \033[32mlibftprintf: Compiled\033[0m"

$(OBJ)	:		$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
				@$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $<
				@echo ".\c"

clean:
				@rm -rf $(DIROBJ)
				@echo "\033[31m> \033[33mlibftprintf: Directory cleaned\033[0m"

fclean: clean
				@rm -f $(NAME)
				@echo "\033[31m> \033[33mRemove libftprintf.a\033[0m"

re: fclean all

$(DIROBJ):
				@mkdir -p $(DIROBJ)
				@mkdir -p $(DIROBJ)/ft_printf

.NOTEPARALLEL: all $(NAME) re
