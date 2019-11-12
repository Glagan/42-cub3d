# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 12:45:02 by ncolomer          #+#    #+#              #
#    Updated: 2019/11/12 16:37:58 by ncolomer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.c cub3d.c game.c bmp.c \
					config/config.c config/map.c config/map_check.c \
					config/parse_params.c config/parse_texture.c \
					utils/ft_strlen.c utils/ft_substr.c utils/ft_in_set.c \
					utils/str.c utils/ft_strdup.c utils/ft_split.c utils/ft_atoi.c \
					utils/pos.c utils/ft_itoa.c utils/ft_memmove.c \
					utils/ft_strcmp.c utils/ft_write.c utils/ft_endwith.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c \
					engine/window.c engine/camera.c engine/shortcuts.c \
					engine/raycast.c engine/draw.c engine/sprite.c \
					engine/color.c engine/screen.c engine/ui.c \
					engine/texture.c engine/tables.c engine/draw_wall.c \
					engine/draw_sky_floor.c engine/quest.c \
					engine/sprite_utils.c engine/crosshair.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re