# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 17:40:40 by jaicastr          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2026/03/11 18:39:21 by asoria           ###   ########.fr        #
=======
#    Updated: 2026/03/11 22:32:48 by jaicastr         ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #
#
NAME			:=	miniRT
CC				:=	clang
OBJDIR			:=	build
LIBFT_FOLDER	:=	libft
SCANNER			:=	scan-build
CC_GCC			:=	gcc
MLX_FOLDER		:=	minilibx-linux
INCLUDES		:=	-Iinclude -I$(LIBFT_FOLDER)/include -I$(MLX_FOLDER)
LIBPATHS		:=  -L$(LIBFT_FOLDER) -L$(MLX_FOLDER)
LDFLAGS			:=	-Wl,--gc-sections -Wl,-O3 -Wl,-z,now $(LIBPATHS) -lft -lmlx -lXext -lX11 -lm
WARNS			:=	-Wall -Wextra -Werror -Wshadow -Wattributes -fstrict-aliasing -Wpedantic -std=c99 \
					-Waddress -Wambiguous-ellipsis -Wambiguous-macro -Wassume -Wpessimizing-move \
					-Wgnu-union-cast -Wlanguage-extension-token -Wgnu-statement-expression-from-macro-expansion \
					-Wbounds-safety-counted-by-elt-type-unknown-size -Wstrict-aliasing -Wcast-function-type-strict \
					-Wcast-function-type-mismatch -Wc99-compat -Wbool-conversions -Wbool-operation -Wbitwise-instead-of-logical \
					-Wbitfield-enum-conversion -Warray-bounds-pointer-arithmetic -Wnull-pointer-arithmetic \
					-Wredundant-decls -Wno-strict-prototypes -Wnull-dereference -Wundef -Wformat-security -Wformat=2 \
					-Wwrite-strings -Wold-style-definition -Wuninitialized -Wloop-analysis -Wpointer-arith \
					-Wcomma -Wover-aligned -Wmissing-prototypes -Wunused -Wtautological-compare -Wunreachable-code -Wvla
MARCH			:=	-march=native
CFLAGS_BASE		:=	-O3 -pipe -ffunction-sections -fdata-sections -fvectorize -finline-functions \
					-fvisibility=hidden -fstack-protector-strong -fcf-protection=full -ftrivial-auto-var-init=zero \
					-fno-common -fstack-clash-protection -g3
CFLAGS_DEBUG	:=	-O0 -pipe -ffunction-sections -fdata-sections -finline-functions \
					-fvisibility=hidden -fstack-protector-strong -fcf-protection=full -ftrivial-auto-var-init=zero \
					-fno-common -fstack-clash-protection -g3
SANITIZE		:= 	-fsanitize=address,alignment,undefined -fsanitize-recover=null
CFLAGS			:=	$(MARCH) $(CFLAGS_BASE) $(WARNS)
SRCS			:=	src/main.c\
					src/rt_parser/rt_parser.c\
					src/rt_parser/rt_parse_color.c\
					src/rt_parser/rt_parse_coords.c\
					src/rt_parser/rt_parse_sphere.c\
					src/rt_parser/rt_parse_plane.c\
					src/rt_parser/rt_parse_camera.c\
					src/rt_parser/rt_parse_cylinder.c\
					src/rt_parser/rt_parse_light.c\
					src/rt_parser/rt_parse_ambient.c\
					src/rt_parser/rt_init_aos.c\
					src/rt_parser/rt_aos_to_soa.c\
					src/rt_parser/rt_aos_to_soa_plane.c\
					src/rt_parser/rt_aos_to_soa_cylinder.c\
					src/rt_parser/rt_aos_to_soa_light.c\
					src/rt_parser/rt_aos_to_soa_sphere.c\
					src/rt_parser/rt_parse_display_size.c\
					src/rt_mlx/rt_key_hooks.c\
					src/rt_mlx/rt_mouse_hooks.c\
					src/rt_render/rt_render.c\
					src/rt_render/rt_render_hotloop.c\
					src/rt_logger/rt_print_plane.c \
					src/rt_logger/rt_print_cylinder.c \
					src/rt_logger/rt_print_camera.c \
					src/rt_logger/rt_print_sphere.c \
					src/rt_logger/rt_print_light.c \
					src/rt_logger/rt_print_aos.c \
					src/rt_logger/rt_print_soa.c \
					src/rt_logger/rt_errors.c
OBJS			:=	$(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))
COMMON_OBJe		:=	$(filter-out $(OBJDIR)/main.o,$(OBJS))
TEST_SRCS 		:=	tests/rt_parse_coord_test.c \
					tests/rt_parse_color_test.c \
					tests/rt_parse_sphere.c \
					tests/rt_parse_light.c \
					tests/rt_parse_cylinder.c \
					tests/rt_parse_camera.c \
					tests/rt_parse_ambient.c \
					tests/rt_parse_plane.c
TEST_OBJS		:=	$(patsubst tests/%.c,$(OBJDIR)/tests/%.o,$(TEST_SRCS))
TEST_BINS		:=	$(patsubst tests/%.c,$(OBJDIR)/tests/%,$(TEST_SRCS))

all: $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_FOLDER)

mlx:
	@$(MAKE) -C $(MLX_FOLDER)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -g3 -c $< -o $@

$(NAME): $(OBJS) libft mlx
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

sanitize: $(OBJS) libft mlx
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o miniRTSan $(SANITIZE)

debug: libft mlx
	@$(MAKE) $(OBJS) CFLAGS="$(MARCH) $(CFLAGS_DEBUG) $(WARNS)"
	@$(MAKE) re -C $(LIBFT_FOLDER) CFLAGS="$(MARCH) $(CFLAGS_DEBUG) $(WARNS_CLANG)"
	$(CC) $(CFLAGS_DEBUG) $(OBJS) $(LDFLAGS) -o miniRTdbg

clean:
	@$(MAKE) clean -C $(LIBFT_FOLDER)
	@$(MAKE) clean -C $(MLX_FOLDER)
	@rm -rf $(OBJDIR)

static_analysis:
	@$(SCANNER) $(CC) $(WARNS_CLANG) $(CFLAGS_CLANG) $(MARCH) \
		-Xclang -analyzer-output=text --analyze $(filter %.c,$(SRCS)) $(INCLUDES)
	@$(SCANNER) $(CC) $(WARNS_CLANG) $(CFLAGS_BASE_CLANG)\
		-Xclang -analyzer-output=text --analyze $(filter %.c,$(SRCS)) $(INCLUDES)
	@$(CC_GCC) $(WARNS_GCC) $(CFLAGS_GCC) $(MARCH)\
		-fanalyzer $(filter %.c,$(SRCS)) $(INCLUDES) -c && rm *.o
	@$(CC_GCC) $(WARNS_GCC) $(CFLAGS_BASE_GCC)\
		-fanalyzer $(filter %.c,$(SRCS)) $(INCLUDES) -c && rm *.o
	@norminette src/ include/ tests/ $(LIFT_FOLDER)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_FOLDER)
	@rm -f $(NAME)*

$(OBJDIR)/tests/%.o: tests/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -g3 -c $< -o $@

$(OBJDIR)/tests/%: $(OBJDIR)/tests/%.o $(COMMON_OBJS) libft mlx
	$(CC) $(CFLAGS) $< $(COMMON_OBJS) $(LDFLAGS) $(SANITIZE) -o $@

test: $(TEST_BINS)
	@for bin in $(TEST_BINS); do \
		./$$bin || exit 1; \
	done

analyze: test static_analysis
	@$(MAKE) analyze -C $(LIBFT_FOLDER)

re: fclean all

.PHONY: all clean fclean re libft mlx test static_analysis analyze
MAKEFLAGS += --no-print-directory
