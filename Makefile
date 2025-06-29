CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude
NAME = cub3D

LIBFT_DIR = libft_42
LDFLAGS = -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/libft.a

# MLX42_FLAGS = -lmlx42 -lm -lpthread -ldl -lglfw
MLX42_FLAGS = -L/home/msalim/MLX42/build -lmlx42 -lm -lpthread -ldl -lglfw
SRC_DIR = src
OBJS_DIR = objs

SRC =  	main.c \
		exit_handler/exit_handler.c \
		exit_handler/free_map.c \
		parsing/parse.c \
		parsing/parse_utils.c \
		parsing/parse_colors.c \
		parsing/parse_texture.c \
		parsing/parse_content.c \
		parsing/check_map.c \
		parsing/check_map_walls.c \
		parsing/validation_utils.c \
		init/init_game.c \
		init/init_mlx.c \
		game/raycasting/setup_ray.c \
		game/raycasting/draw.c \
		game/raycasting/draw_utils.c \
		game/raycasting/init_rays.c \
		game/start_game.c \
		game/user_events/movement.c	\
		game/user_events/rotation.c	\
		game/user_events/key_handler.c	\
		colors/color_utils.c \

		
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(MLX42_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

# Rule to create .o files while preserving the subdirectory structure
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)  # Ensure subdirectories exist
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
