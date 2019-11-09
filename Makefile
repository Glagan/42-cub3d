# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 12:45:02 by ncolomer          #+#    #+#              #
#    Updated: 2019/11/09 12:23:12 by ncolomer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.c cub3d.c game.c \
					config/config.c config/map.c config/map_check.c \
					config/parse_params.c \
					utils/ft_strlen.c utils/ft_substr.c utils/ft_in_set.c \
					utils/str.c utils/ft_strdup.c utils/ft_split.c utils/ft_atoi.c \
					utils/pos.c utils/ft_itoa.c utils/ft_memmove.c \
					utils/ft_strcmp.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c \
					engine/window.c engine/camera.c engine/shortcuts.c \
					engine/raycast.c engine/draw_image.c engine/sprite.c \
					engine/color.c engine/screen.c engine/ui.c \
					engine/texture.c engine/tables.c  \
					engine/sprite_utils.c engine/crosshair.c \
					libattopng/create_png.c libattopng/libattopng.c \
					libattopng/libattopng2.c libattopng/libattopng3.c \
					libattopng/libattopng4.c libattopng/libattopng5.c \
					libattopng/libattopng6.c libattopng/libattopng7.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -g -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

NAME			= cub3d

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re