# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/13 18:15:02 by cschabra      #+#    #+#                  #
#    Updated: 2023/03/28 17:41:18 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= pipex
CFLAGS= -Wall -Wextra -Werror $(HEADERS) #-fsanitize=address 

LIBFT= 42lib

HEADERS= -I include -I $(LIBFT)/include
LIBS= $(LIBFT)/libft.a

CFILES= ./src/childproc.c \
./src/errors.c \
./src/findexec.c \
./src/main.c

OBJECTS= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(MAKE) -C $(LIBFT)
	@$(CC) -o $(NAME) $(CFLAGS) $(CFILES) $(LIBS)

clean:
	rm  -f $(OBJECTS)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug