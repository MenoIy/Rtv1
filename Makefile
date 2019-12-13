# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msidqi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 00:08:25 by msidqi            #+#    #+#              #
#    Updated: 2019/07/24 19:26:57 by kdaou            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
LIBFT = libft.a
LIBGL = libgl.a
LIBMLX = libmlx.a
LIBFTL = libft/libft.a
LIBGLL = src/libgl/libgl.a
LIBMLXL = src/minilibx_macos/libmlx.a
SRC_PATH = src
GLSRC_PATH = src/libgl
SRC = ft_event_system_mlx.c ft_get_plane_config.c \
ft_plane_functions.c ft_vector_sub.c ft_events_keyboard.c \
ft_get_ray_to_light.c ft_sphere_functions.c get_next_line.c \
ft_expect.c ft_get_sphere_config.c ft_utils_func.c \
ft_atof.c ft_expect_matrix.c ft_image_setup_mlx.c ft_vec_create.c \
ft_camera.c ft_get_camera_config.c ft_light_intersection.c \
ft_vec_cross_dot_prod.c ft_color_operations.c ft_get_cone_config.c \
ft_matrix_operations.c ft_vec_destroy.c ft_cone_functions.c ft_get_config.c \
ft_min_max.c ft_vec_normalize_magnitude.c ft_cylinder_functions.c \
ft_get_cylinder_config.c ft_vec_scalar.c ft_draw.c \
ft_get_light_config.c ft_vector_add.c ft_error_management.c \
ft_get_matrix.c ft_parsing_tools.c ft_vector_operations.c
INCLUDE = include
INC = include/libgl.h
OBJS_DIR = .objs
CC = gcc -Wall -Wextra -Werror 
FLAGS = -framework OpenGl -framework Appkit -lmlx
OBJ = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

all : $(NAME)

$(OBJ) : $(OBJS_DIR)/%.o : $(GLSRC_PATH)/%.c $(INC)| $(OBJS_DIR)
	$(CC) -c $< -o $@ -I$(INCLUDE)
$(LIBGLL) : $(OBJ)
	ar rc $@ $^
	ranlib $@
$(LIBFTL) :
	make -C libft
$(NAME) : $(LIBFTL) $(LIBGLL) $(SRC_PATH)/main.c
	$(CC) -o $@ $< $(word 2,$^) $(word 3,$^) -I$(INCLUDE)  $(FLAGS) 

clean : 
	rm -rf $(OBJ) $(LIBGLL) $(LIBFTL)
	make clean -C libft
fclean : clean
	rm -rf $(NAME)
	make fclean -C libft
re : fclean all

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
