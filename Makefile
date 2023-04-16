NAME		=	chipx8.out
VERSION		=	0.0.1

SRCS		=	srcs/main.c \
				srcs/renderer.c \
				srcs/components.c \
				srcs/tasks.c \
				srcs/init.c \
				srcs/rom.c \
				srcs/debug.c \
				srcs/operations.c \
				srcs/window.c

HEADERS		=	includes

BUILDDIR	=	.build
OBJS		=	$(SRCS:%.c=$(BUILDDIR)/%.o)
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
SDLFLAGS	=	`sdl2-config --cflags --libs`
RM			=	rm -Rf
MAKE		=	make -C
MKDIR		=	mkdir
ECHO		=	echo -e

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(SDLFLAGS) -lncurses

$(BUILDDIR)/%.o	:	%.c $(HEADERS)/*.h Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

clean :
	-rm -f $(OBJS)

fclean : clean
	-rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re