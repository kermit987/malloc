##
## Makefile for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Memoire/PSU_2015_malloc
## 
## Made by Karmes Lionel
## Login   <karmes_l@epitech.net>
## 
## Started on  Mon Jan 25 16:24:31 2016 Karmes Lionel
## Last update Sun Feb 14 13:06:17 2016 Karmes Lionel
##

CC	=	gcc

RM	=	rm -f

CFLAGS	+=	-Wextra -Wall -Werror -lpthread
CFLAGS	+=	-I./include/

LDFLAGS	=

SRCS	=	show_alloc_mem.c \
		malloc.c \
		free.c \
		realloc.c 

NAME	=	libmy_malloc.so

OBJS	=	$(SRCS:.c=.o)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -c -fpic $(SRCS) $(CFLAGS)
		$(CC) -shared -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean clean all

.PHONY:		all clean fclean re
