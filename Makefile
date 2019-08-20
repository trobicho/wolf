# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 14:52:42 by trobicho          #+#    #+#              #
#    Updated: 2019/08/20 04:08:45 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	= 	-g #-Wall -Wextra -Werror

SRCS	=	main.c \
			input.c \
			init.c \
			wolf.c \
			player.c \
			render.c \
			ray_cast.c \
			physic.c \
			map.c \
			vector.c

HDRS	=	init.h \
			input.h \
			wolf.h \
			player.h \
			render.h \
			ray_cast.h \
			physic.h \
			map.h \
			vector.h
OUTS	=	$(SRCS:.c=.o)
NAME	=	wolf
SDL_LOC	=	$(HOME)/.brew/Cellar/sdl2/2.0.9_1
LFLAGS	=	-lm -L $(SDL_LOC)/lib -lSDL2 -L./libft -lf
IFLAGS	=	-I $(SDL_LOC)/include

all:		$(NAME) Makefile

$(NAME):	$(OUTS) Makefile
	echo $(OUTS)
	$(CC) $(OUTS) $(CFLAGS) $(LFLAGS) -o $(NAME)

%.o:		%.c $(SRCS) $(HDRS) Makefile
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
