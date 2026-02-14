CC := cc
CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS = -lSDL2 -lm

NAME := so_long

OUTPUT_DIR := output

SRC_DIR := src

LIST_SRC := list/list.c \
			list/pop.c \
			list/utils.c \
			list/utils2.c \
			list/iterators.c \
			list/get.c

GNL_SRC := gnl/get_next_line_bonus.c \
      gnl/get_next_line_utils_bonus.c

SRC := $(GNL_SRC) $(LIST_SRC) \
	  $(SRC_DIR)/drawing.c \
	  $(SRC_DIR)/drawing_utils.c \
	  $(SRC_DIR)/high_level_drawing.c \
	  $(SRC_DIR)/input_handling.c \
	  $(SRC_DIR)/player_management.c \
	  $(SRC_DIR)/timings.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/mice.c \
	  $(SRC_DIR)/atlas.c \
	  $(SRC_DIR)/map.c \
	  $(SRC_DIR)/map_loader.c \
	  $(SRC_DIR)/assets_loading.c \
	  $(SRC_DIR)/app_setup.c \
	  $(SRC_DIR)/cleaning.c \
	  $(SRC_DIR)/decoration.c \
	  $(SRC_DIR)/transition.c \
	  $(SRC_DIR)/map_checker.c \
	  $(SRC_DIR)/gameplay.c \
	  $(SRC_DIR)/particles.c \
	  $(SRC_DIR)/not_an_easter_egg.c \
	  $(SRC_DIR)/map_checker2.c \
	  $(SRC_DIR)/hud.c \
	  $(SRC_DIR)/easing.c

INCLUDES := list,gnl,libft,ft_printf,include,MacroLibX

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)

$(NAME): $(OUTPUT_DIR) $(OBJ) $(OUTPUT_DIR)/main.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a
	$(CC) $(OBJ) $(OUTPUT_DIR)/main.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a $(CFLAGS) $(LDFLAGS) -o $@

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)/gnl $(OUTPUT_DIR)/list

$(OUTPUT_DIR)/main_bonus.o: $(SRC_DIR)/main_bonus.c $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

$(OUTPUT_DIR)/main.o: $(SRC_DIR)/main.c $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

MacroLibX/libmlx.so:
	make -C MacroLibX -j10

libft/libft.a:
	make -C libft

ft_printf/libftprintf.a:
	make -C ft_printf

all: $(NAME)

bonus: $(OUTPUT_DIR) $(OBJ) $(OUTPUT_DIR)/main_bonus.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a
	$(CC) $(OBJ) $(OUTPUT_DIR)/main_bonus.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OUTPUT_DIR)
	make -C MacroLibX fclean
	make -C libft fclean
	make -C ft_printf fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean bonus
