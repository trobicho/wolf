# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 14:52:42 by trobicho          #+#    #+#              #
#    Updated: 2019/08/30 02:20:04 by trobicho         ###   ########.fr        #
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
			ray_utils.c \
			physic.c \
			map.c \
			vector.c \
			menu.c \
			editor.c \
			editor_utils.c \
			editor_map.c \
			editor_hud.c \
			ppm.c \
			ppm_load.c \
			ppm_utils.c \
			draw.c

HDRS	=	init.h \
			input.h \
			wolf.h \
			player.h \
			render.h \
			ray_cast.h \
			ray_utils.h \
			physic.h \
			map.h \
			vector.h \
			menu.h \
			editor.h \
			editor_utils.h \
			editor_hud.h \
			ppm.h \
			ppm_load.h \
			ppm_utils.h \
			draw.h

OUTS	=	$(SRCS:.c=.o)
NAME	=	wolf3d
SDL_LOC	=	$(HOME)/.brew/Cellar/sdl2/2.0.9_1
TTF_LOC	=	$(HOME)/.brew/Cellar/sdl2_ttf/2.0.15
LFLAGS	=	-lm -L $(SDL_LOC)/lib -lSDL2 -L$(TTF_LOC)/lib -lSDL2_ttf -L./libft -lft
IFLAGS	=	-I $(SDL_LOC)/include/SDL2 -I $(SDL_LOC)/include -I $(TTF_LOC)/include -I ./libft

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
