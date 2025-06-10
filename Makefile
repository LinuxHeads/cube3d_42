CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude
NAME = cube3d

LIBFT_DIR = libft_42
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_FLAGS = -lmlx42 -lm -lpthread -ldl -lglfw
SRC_DIR = src
OBJS_DIR = objs


SRC =  	main.c \
		exit_handler.c \
		parsing/parse.c \
		parsing/parse_utils.c \
		parsing/parse_colors.c \
		parsing/parse_texture.c \
		parsing/parse_content.c \
		parsing/check_map.c \
		parsing/validation_utils.c \
		init/init.c \
		init/init_mlx.c \
		game/setup_ray.c \
		game/start_game.c \
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
