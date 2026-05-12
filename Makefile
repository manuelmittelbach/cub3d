# =========================================================
# Name des finalen Binaries
# =========================================================
NAME		= cub3D

# =========================================================
# Compiler und Flags
# cc wie bei dir, Flags aus deinem bisherigen Stil
# =========================================================
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP -g -O0
MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a

# =========================================================
# Ordner
# =========================================================
SRC_DIR		= src
OBJ_DIR		= build
INC_DIR		= inc

# =========================================================
# ---------------------------------------------------------
# 1) Projekt-Sources
#    -> exakt aus deiner aktuellen Struktur
#    -> wenn du neue Dateien anlegst, hier ergänzen
# ---------------------------------------------------------
# =========================================================
SRCS		= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing/check_input_file.c \
	$(SRC_DIR)/parsing/check_map_elements.c \
	$(SRC_DIR)/parsing/parse_map.c \
	$(SRC_DIR)/parsing/validate_map.c \
	$(SRC_DIR)/mlx/init.c \
	$(SRC_DIR)/mlx/mlx_cleanup.c \
	$(SRC_DIR)/mlx/pixel_put.c \
	$(SRC_DIR)/raycaster/cast_rays.c \
	$(SRC_DIR)/raycaster/dda.c \
	$(SRC_DIR)/raycaster/init_ray.c \
	$(SRC_DIR)/raycaster/render.c \
	$(SRC_DIR)/raycaster/render_wall.c \
	$(SRC_DIR)/mlx/textures.c \
	$(SRC_DIR)/player/events.c \
	$(SRC_DIR)/player/player_movements.c \
	$(SRC_DIR)/minimap/init_mm.c \
	$(SRC_DIR)/minimap/minimap.c \
	$(SRC_DIR)/utils/get_next_line.c \
	$(SRC_DIR)/utils/get_next_line_utils.c \
	$(SRC_DIR)/utils/utils_1.c \


# =========================================================
# ---------------------------------------------------------
# 2) Libft-Sources
#    -> aus src/libft
#    -> ohne ft_testmain.c
#    -> werden genauso in build/libft/... gelegt
# ---------------------------------------------------------
# =========================================================
LIBFT_DIR	= $(SRC_DIR)/libft
LIBFT_SRCS	= \
	$(LIBFT_DIR)/ft_atoi.c \
	$(LIBFT_DIR)/ft_bzero.c \
	$(LIBFT_DIR)/ft_calloc.c \
	$(LIBFT_DIR)/ft_isalnum.c \
	$(LIBFT_DIR)/ft_isalpha.c \
	$(LIBFT_DIR)/ft_isascii.c \
	$(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_isprint.c \
	$(LIBFT_DIR)/ft_itoa.c \
	$(LIBFT_DIR)/ft_memchr.c \
	$(LIBFT_DIR)/ft_memcmp.c \
	$(LIBFT_DIR)/ft_memcpy.c \
	$(LIBFT_DIR)/ft_memmove.c \
	$(LIBFT_DIR)/ft_memset.c \
	$(LIBFT_DIR)/ft_putchar_fd.c \
	$(LIBFT_DIR)/ft_putendl_fd.c \
	$(LIBFT_DIR)/ft_putnbr_fd.c \
	$(LIBFT_DIR)/ft_putstr_fd.c \
	$(LIBFT_DIR)/ft_split.c \
	$(LIBFT_DIR)/ft_strchr.c \
	$(LIBFT_DIR)/ft_strcmp.c \
	$(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_striteri.c \
	$(LIBFT_DIR)/ft_strjoin.c \
	$(LIBFT_DIR)/ft_strlcat.c \
	$(LIBFT_DIR)/ft_strlcpy.c \
	$(LIBFT_DIR)/ft_strlen.c \
	$(LIBFT_DIR)/ft_strmapi.c \
	$(LIBFT_DIR)/ft_strncmp.c \
	$(LIBFT_DIR)/ft_strnstr.c \
	$(LIBFT_DIR)/ft_strrchr.c \
	$(LIBFT_DIR)/ft_strtrim.c \
	$(LIBFT_DIR)/ft_substr.c \
	$(LIBFT_DIR)/ft_tolower.c \
	$(LIBFT_DIR)/ft_toupper.c

# =========================================================
# Objekte
# src/... -> build/...
# =========================================================
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT_OBJS	= $(LIBFT_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ALL_OBJS	= $(OBJS) $(LIBFT_OBJS)
DEPS		= $(ALL_OBJS:.o=.d)

# =========================================================
# Default-Target
# =========================================================
all: $(NAME)

# =========================================================
# Link-Schritt
# - alle Objektdateien linken
# - readline wird mitgelinkt
# =========================================================
$(NAME): $(MLX_LIB) $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) -o $@ -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# =========================================================
# Generische Regel:
# build/.../.o aus src/.../.c erzeugen
# mkdir -p sorgt dafür, dass die Ordnerstruktur in build/ existiert
# =========================================================
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# =========================================================
# Aufräumen
# =========================================================
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

bonus: all

-include $(DEPS)

.PHONY: all clean fclean re bonus
