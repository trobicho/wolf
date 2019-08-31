# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 14:52:42 by trobicho          #+#    #+#              #
#    Updated: 2019/08/31 21:49:08 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	= 	-g #-Wall -Wextra -Werror

SRCS_PATH	=	./srcs
HDRS_PATH	=	./hdrs
OBJS_PATH	=	./objs

SRCS_NAME	=	main.c \
				input.c \
				init.c \
				wolf.c \
				door.c \
				player.c \
				render.c \
				ray_cast.c \
				ray_utils.c \
				ray_door.c \
				physic.c \
				map.c \
				map_alloc.c \
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

HDRS_NAME	=	init.h \
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

OBJS_NAME	=	$(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
HDRS = $(addprefix $(HDRS_PATH)/, $(HDRS_NAME))
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

NAME	=	wolf3d
SDL_LOC	=	$(HOME)/.brew/Cellar/sdl2/2.0.9_1
TTF_LOC	=	$(HOME)/.brew/Cellar/sdl2_ttf/2.0.15
LFLAGS	=	-lm -L $(SDL_LOC)/lib -lSDL2 -L$(TTF_LOC)/lib -lSDL2_ttf -L./libft -lft
IFLAGS	=	-I $(HDRS_PATH) -I $(SDL_LOC)/include/SDL2 -I $(SDL_LOC)/include -I $(TTF_LOC)/include -I ./libft

all:		$(NAME) Makefile

$(NAME):	$(OBJS) Makefile
	echo $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c $(HDRS) Makefile
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
