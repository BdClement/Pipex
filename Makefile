# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 13:25:27 by clbernar          #+#    #+#              #
#    Updated: 2023/04/12 14:29:36 by clbernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRCS = pipex.c child.c
B_SRCS = pipex_bonus.c child_bonus.c

#GNL_PATH = ./Get_Next_Line
#GNL_SRCS = $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c

LIB = $(LIBFT_PATH)/libft.a
LIBFT_PATH = ./Libft

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
#GNL_OBJ = get_next_line.o get_next_line_utils.o

INC = $(LIBFT_PATH)

all : $(NAME)

#Comprendre pourquoi le bonus relink et pas le make simple
$(NAME) : $(LIB) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft

%.o : %.c
	$(CC) -I$(INC) $(CFLAGS) -c $<
#-I$(INC) Besoin d'Ajouter "Get_Next_Line/get_next_line.h"dans mon header de .h

#gnl : $(GNL_SRCS)
#	$(CC) ./Get_Next_Line/get_next_line.h $(CFLAGS) -c $< ./Get_Next_Line/get_next_line.c ./Get_Next_Line/get_next_line_utils.c

$(LIB):
	make -C Libft/
	make bonus -C Libft/

bonus : $(LIB) $(B_OBJS)
	$(CC) -o $(NAME) $(B_OBJS) -L$(LIBFT_PATH) -lft

git :
	git add *
	git commit -m c
	git push

clean:
	$(RM) $(OBJS) $(B_OBJS) $(GNL_OBJ)
	make fclean -C Libft/

fclean: clean
	 $(RM) $(NAME)

re: fclean all

.PHONY : re all fclean bonus clean
