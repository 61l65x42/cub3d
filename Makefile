NAME                :=      cub3D
CC					:=		gcc
RM 					:=		rm -rf
OS					:=		$(shell uname -s)

PATH_BUILD          :=      build
PATH_LIBFT          :=      libft
PATH_LIBMLX_MAC     :=      dependencies/minilibx-macos
PATH_LIBMLX_LINUX   :=      dependencies/minilibx-linux
PATH_LIBMLX42       :=      dependencies/MLX42/

SRCS_COMMON := \
    srcs/exit/free_texture.c \
    srcs/exit/free_all.c \
    srcs/extract/extract_main.c \
    srcs/extract/extract_map.c \
    srcs/extract/extract_map_finalize.c \
    srcs/extract/extract_scene.c \
    srcs/extract/extract_scene_extras.c \
    srcs/extract/extract_utils.c \
    srcs/extract/validate_map.c \
    srcs/extract/validate_scene.c \
    srcs/main.c \
    srcs/play/draw/walls_ceiling_floor/draw_wall_ray.c \
    srcs/play/draw/walls_ceiling_floor/draw_floor_ceiling.c \
    srcs/play/draw/walls_ceiling_floor/get_wall_data_ray.c \
    srcs/play/draw/extras/draw_gun.c \
    srcs/play/draw/extras/draw_sprites.c \
    srcs/play/draw/extras/draw_take_damage.c \
    srcs/play/draw/extras/draw_healthbars.c \
    srcs/play/draw/gamemenu/draw_menu.c \
    srcs/play/draw/gamemenu/input_game_menu.c \
    srcs/play/draw/gameover/draw_game_over.c \
    srcs/play/draw/gameover/input_game_over.c \
    srcs/play/draw/minimap/minimap.c \
    srcs/play/play.c \
    srcs/play/prepare/player.c \
    srcs/play/prepare/textures/load_textures.c \
    srcs/play/prepare/textures/load_weapons.c \
    srcs/play/prepare/textures/prepare_map_specials.c \
    srcs/play/prepare/textures/weapon_positions.c \
	srcs/play/prepare/hooks/events.c \
    srcs/play/renderables/collect_renderables.c \
    srcs/play/renderables/renderables.c \
    srcs/play/update/cast_ray/ray_cast.c \
    srcs/play/update/player/player_pos.c \
    srcs/play/update/player/player_taking_damage.c \
    srcs/play/update/shooting/handle_shooting.c \
    srcs/play/update/shooting/handle_shooting_hits.c \
    srcs/play/update/shooting/handle_shooting_traverse.c \
    srcs/play/update/shooting/switch_weapon.c \
    srcs/play/update/sprites/update_sprite_render_info.c \
    srcs/play/update/sprites/update_sprites.c \
    srcs/play/update/sprites/update_sprite_position.c \
    srcs/utils/blend_colors.c \
    srcs/utils/free_str_utils.c \
    srcs/utils/math_utils.c \
    srcs/utils/t_map.c \
    srcs/utils/str_to_long.c

ifeq ($(OS),Linux)
    SRCS_PLATFORM := \
        srcs/exit/exit_linux.c \
        srcs/play/prepare/hooks/mouse_linux.c
else
    SRCS_PLATFORM := \
        srcs/exit/exit_macos.c \
        srcs/play/prepare/hooks/mouse_macos.c
endif

SRCS := $(SRCS_COMMON) $(SRCS_PLATFORM)
OBJS				:=		$(SRCS:%.c=$(PATH_BUILD)/%.o)
DEPS				:=		$(OBJS:.o=.d)

FLAG_INC			:= 		$(addprefix -I, includes $(PATH_LIBFT) $(PATH_LIBMLX_LINUX) $(PATH_LIBMLX_MAC) $(PATH_LIBMLX42)include)
FLAGS_COMP			:= 		-O3 -Wall -Wextra -Werror $(FLAG_INC) -MMD -MP -g 

FLAG_LIBFT			:=		-L$(PATH_LIBFT) -lft 
FLAG_LIBMLX_MAC		:=		-L$(PATH_LIBMLX_MAC) -lmlx -framework OpenGL -framework AppKit -lz
FLAG_LIBMLX_LINUX	:=		-L$(PATH_LIBMLX_LINUX) -lmlx -lX11 -lXext
FLAG_LIBMLX42		:= 		-L$(PATH_LIBMLX42)build -lmlx42 -lglfw -ldl

ifeq ($(OS),Linux)
	FLAGS_LINKING := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_LINUX) $(FLAG_LIBMLX42)
	FLAGS_COMP += -D LINUX
else
	FLAGS_LINKING := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_MAC) $(FLAG_LIBMLX42)
	GLFW_PATH_MAC = /Users/$(USER)/.brew/opt/glfw/lib/
	FLAGS_LINKING += -L$(GLFW_PATH_MAC)
endif

all:						init $(NAME)
							@printf "\033[0;32mGame $(NAME) created. 🎮\033[0m\n"

init:
							@ make -s -C $(PATH_LIBFT)
ifeq ($(OS),Linux)
	@ make -C $(PATH_LIBMLX_LINUX)
	@ cmake -S $(PATH_LIBMLX42) -B $(PATH_LIBMLX42)build && make -C $(PATH_LIBMLX42)build -j4
else
	@ make -C $(PATH_LIBMLX_MAC)
	@ cmake -S $(PATH_LIBMLX42) -B $(PATH_LIBMLX42)build && make -C $(PATH_LIBMLX42)build -j4
endif

$(NAME):					$(OBJS)
							@$(CC) $(OBJS) $(FLAGS_LINKING) -o $@

$(PATH_BUILD)/%.o:	%.c
							@mkdir -p $(dir $@)
							@$(CC) $(FLAGS_COMP) -c $< -o $@
							@printf "\033[0;33mCompiling  $< 🔨\033[0m\n"

bonus:						all

clean:
							@ $(RM) $(PATH_BUILD)
							@ make -s -C $(PATH_LIBFT) clean
							@ make -s -C $(PATH_LIBMLX_MAC) clean
							@ make -s -C $(PATH_LIBMLX_LINUX) clean
							@ make -C $(PATH_LIBMLX42)build clean

fclean:						clean
							@ $(RM) $(NAME)
							@ make -s -C $(PATH_LIBFT) fclean
							@ $(RM) $(PATH_LIBMLX42)build

re:							fclean all

.PHONY:						all clean fclean re

-include $(DEPS)
