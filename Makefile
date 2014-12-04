##
## Makefile for  in /home/maret_a/rendu/PSU_2013_malloc
## 
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
## 
## Started on  04/02/2014 17:09
##

SRCS	=	thread.c \
		malloc.c \
		realloc.c \
		free.c \
		show_alloc_mem.c

CFLAGS	=	-W -Wall -Wextra

OBJS	=	$(SRCS:.c=.o)

NAME	=	libmy_malloc_$(HOSTTYPE).so

LINK	=	libmy_malloc.so

all:	$(NAME)

$(NAME):
	rm -f $(LINK)
	gcc -fPIC -shared $(SRCS) -o $(NAME)
	ln --symbolic $(NAME) $(LINK)
debug:
	rm -f $(LINK)
	gcc -fPIC -shared malloc_debug.c -o $(NAME)
	ln --symbolic $(NAME) $(LINK)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	rm -f libmy_malloc.so

re: fclean all
