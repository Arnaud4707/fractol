.PHONY: $(NAME) all clean fclean re

# -------------- Colors ----------------

GREEN  = '\033[0;32m'
RED    = '\033[0;31m'
BRUN   = '\033[0;33m'
WHITE  = '\033[1;37m'
RESET  = '\033[0m'

# -------------- Programme Name --------

NAME = prog

# -------------- LIBS ------------------

LIB_FRACTAL_DIR= lib/
LIB_FRACTAL_PATH  = libfractol.a
LIB_FRACTAL      = $(addprefix $(LIB_FRACTAL_DIR), $(LIB_FRACTAL_PATH))

LIBFT_LIB  = libft.a
LIBF_PATH  = libft/
LIBFT      = $(LIBF_PATH)$(LIBFT_LIB)

MLX_PATH = mlx/
LIB_MLX  = libmlx.a
MLX      = $(MLX_PATH)$(LIB_MLX)

# -------------- Flags of compilation---

CC     = cc
CFLAGS  = -Wall -Wextra -Werror -I./ -I$(HOME)/.local/include -g3 -O3 -ffast-math -march=native -funroll-loops
LDFLAGS = -L$(HOME)/.local/lib -lsndfile -lfftw3

# -------------- Sources files ---------

SRC_DIR = fractal/
SRC = animation/animation_buddhabrot.c \
      animation/animation_buddhabrot_2.c \
      animation/animation_mandelbrot.c \
      animation/animation_zoom_mandelbrot.c \
      buddhabrot/buddhabrot.c buddhabrot/buddhabrot_thread.c \
	  burningship/burningship.c \
      dragon_curve/dragon.c \
      event/events.c event/event_bis.c \
	  mandelbrot/mandelbrot.c \
	  julia/julia.c \
      src/color_b.c src/color_c.c src/color_d.c src/color.c \
      src/error.c src/fractal.c \
      src/set_up.c src/utils.c src/verification.c src/zoom.c \
      spong_menger/spong_menger.c \
	  text/start.c
SRC_PATH = $(addprefix $(SRC_DIR), $(SRC))

MENU_DIR = menu/
MENU = menu.c intro.c option.c cube.c wave.c
MENU_PATH = $(addprefix $(MENU_DIR), $(MENU))
# -------------- Object files ----------

OBJ_DIR = $(SRC_DIR)obj/
OBJ      = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_MAIN = $(OBJ_DIR)main.o 
OBJ_AUDIO = $(OBJ_DIR)audio.o 
OBJ_MENU =  $(addprefix $(OBJ_DIR), $(MENU:.c=.o))

# -------------- Rules ------------------

all: $(NAME)

# ----- Compiling Programme ----

$(NAME): $(MLX) $(LIBFT) $(LIB_FRACTAL) $(OBJ_MAIN)
	@echo $(BRUN) "Compiling fractol..."
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_MAIN) $(LIB_FRACTAL) $(LIBFT) -Lmlx -lmlx -L/usr/lib/x86_64-linux-gnu -lXext -lX11 -lm -lz -o $(NAME)
	@echo $(GREEN) "OK : Compile fractol" $(RESET)

# ----- Linking libs -----------

$(LIB_FRACTAL): $(OBJ) $(OBJ_MENU) $(OBJ_AUDIO)
	@ar rcs $(LIB_FRACTAL) $(OBJ) $(OBJ_MENU) $(OBJ_AUDIO)

$(LIBFT):
	@echo $(BRUN) "Making Libft..." $(RESET)
	@make -sC $(LIBF_PATH)
	@echo $(GREEN) "OK $(WHITE): Make Libft" $(RESET)

$(MLX):
	@echo $(BRUN) "Making MiniLibX..." $(RESET)
	@make -sC $(MLX_PATH)
	@echo $(GREEN) "OK $(WHITE): Make MiniLibX" $(RESET)

# ----- Create Object Files ----

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)Compiling fractol 🏹: $(WHITE)$< $(RESET)\n"
	@$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_MAIN): main.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)Compiling main 🏹: $(WHITE)$< $(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(MENU_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)Compiling menu 🏹: $(WHITE)$< $(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: menu/audio.c
	@printf "$(GREEN)Compiling menu 🏹: $(WHITE)$< $(RESET)\n"
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@	

# ----- Bonus ------------------

bonus: all

# ----- Clean Object Files -----

clean:
	@echo $(BRUN) "Removing .o object files..."
	@rm -rf $(OBJ_DIR)
	@echo $(GREEN) "OK : Remove .o object files" $(RESET)

# ----- Clean Libs, Programme --

fclean: clean
	@make clean -C $(MLX_PATH)
	@make fclean -C $(LIBF_PATH)
	@echo $(BRUN) "Removing fractol..."
	@rm -rf $(NAME) $(LIB_FRACTAL)
	@echo $(GREEN) "OK : Remove fractol" $(RESET)

# ----- Fclean + All

re: fclean all
