# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 13:25:27 by clbernar          #+#    #+#              #
#    Updated: 2023/04/04 20:38:44 by clbernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRCS = pipex.c child.c

LIB = $(LIBFT_PATH)/libft.a
LIBFT_PATH = ./Libft

OBJS = $(SRCS:.c=.o)

INC = $(LIBFT_PATH)

all : $(NAME)

$(NAME) : $(LIB) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft

%.o : %.c
	$(CC) -I$(INC) $(CFLAGS) -c $<

$(LIB):
	make -C Libft/
	make bonus -C Libft/

git :
	git add *
	git commit -m c
	git push

clean:
	$(RM) $(OBJS) $(B_OBJS)
	make fclean -C Libft/

fclean: clean
	 $(RM) $(NAME)

re: fclean all

.PHONY : re all fclean bonus clean
