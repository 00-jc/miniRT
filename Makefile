# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 17:40:40 by jaicastr          #+#    #+#              #
#    Updated: 2026/03/17 16:33:45 by jaicastr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ── Output ────────────────────────────────────────────────────────────────────
NAME           := miniRT
OBJDIR         := build

# ── Toolchain ─────────────────────────────────────────────────────────────────
CC             ?= clang
CC_CLANG       := clang
CC_GCC         := gcc
CC_ID          := $(shell $(CC) --version 2>/dev/null | head -1)
SCANNER        := scan-build

# ── Paths ─────────────────────────────────────────────────────────────────────
LIBFT_FOLDER   := libft
MLX_FOLDER     := minilibx-linux
INCLUDES       := -Iinclude -I$(LIBFT_FOLDER)/include -I$(MLX_FOLDER)
LIBPATHS       := -L$(LIBFT_FOLDER)
LIBS		   := -lft -lXext -lX11 -lm

# ── Flags ─────────────────────────────────────────────────────────────────────
MARCH          := -march=native

# ─────────────────────────────────────────────────────────────────────────────
# Warnings: flags supported by BOTH GCC and Clang go in COMMON.
# Compiler-specific additions go in WARNS_CLANG / WARNS_GCC.
# ─────────────────────────────────────────────────────────────────────────────

WARNS_COMMON := -Wall -Wextra -Werror -Wpedantic -std=c99                     \
	-fstrict-aliasing -Wstrict-aliasing                                        \
	-Wshadow                                                                   \
	-Waddress                                                                  \
	-Wattributes                                                               \
	-Wredundant-decls                                                          \
	-Wno-strict-prototypes                                                     \
	-Wmissing-prototypes                                                       \
	-Wold-style-definition                                                     \
	-Wnull-dereference                                                         \
	-Wundef                                                                    \
	-Wformat-security                                                          \
	-Wformat=2                                                                 \
	-Wwrite-strings                                                            \
	-Wuninitialized                                                            \
	-Wpointer-arith                                                            \
	-Wunused                                                                   \
	-Wtautological-compare                                                     \
	-Wunreachable-code                                                         \
	-Wvla                                                                      \
	-Wbool-operation                                                           \
	-Wcast-function-type                                                       \
	-Wimplicit-fallthrough                                                     \
	-Wdouble-promotion                                                         \
	-Wfloat-equal                                                              \
	-Wmissing-noreturn

# ── Clang-only extras ────────────────────────────────────────────────────────
WARNS_CLANG := $(WARNS_COMMON)                                                \
	-Wambiguous-ellipsis                                                       \
	-Wambiguous-macro                                                          \
	-Wassume                                                                   \
	-Wpessimizing-move                                                         \
	-Wgnu-union-cast                                                           \
	-Wlanguage-extension-token                                                 \
	-Wgnu-statement-expression-from-macro-expansion                            \
	-Wbounds-safety-counted-by-elt-type-unknown-size                           \
	-Wcast-function-type-strict                                                \
	-Wcast-function-type-mismatch                                              \
	-Wc99-compat                                                               \
	-Wbool-conversions                                                         \
	-Wbitwise-instead-of-logical                                               \
	-Wbitfield-enum-conversion                                                 \
	-Warray-bounds-pointer-arithmetic                                          \
	-Wnull-pointer-arithmetic                                                  \
	-Wloop-analysis                                                            \
	-Wcomma                                                                    \
	-Wover-aligned                                                             \
	-Wconditional-uninitialized                                                \
	-Wimplicit-float-conversion                                                \
	-Wimplicit-int-conversion                                                  \
	-Wshorten-64-to-32                                                         \
	-Wstring-concatenation                                                     \
	-Wunused-but-set-parameter                                                 \
	-Wsizeof-array-div                                                         \
	-Wtautological-constant-in-range-compare                                   \
	-Wno-extra-semi-stmt                                                       \
	-Wthread-safety                                                            \
	-Wdangling

# ── GCC-only extras ──────────────────────────────────────────────────────────
WARNS_GCC := $(WARNS_COMMON)                                                  \
	-Wshift-overflow                                                           \
	-Wunused-but-set-parameter                                                 \
	-Wstrict-overflow=5                                                        \
	-Wmissing-attributes                                                       \
	-Wmismatched-dealloc                                                       \
	-Wtrivial-auto-var-init                                                    \
	-Wuse-after-free=3                                                         \
	-Wsuggest-attribute=pure                                                   \
	-Wsuggest-attribute=const                                                  \
	-Wsuggest-attribute=noreturn                                               \
	-Wsuggest-attribute=malloc                                                 \
	-Wsuggest-attribute=format                                                 \
	-Wsuggest-attribute=cold                                                   \
	-Walloc-size                                                               \
	-Walloca                                                                   \
	-Warith-conversion                                                         \
	-Warray-bounds=2                                                           \
	-Warray-compare                                                            \
	-Warray-parameter                                                          \
	-Wattribute-alias=2                                                        \
	-Wduplicated-branches                                                      \
	-Wduplicated-cond                                                          \
	-Wzero-length-bounds                                                       \
	-Wunsafe-loop-optimizations                                                \
	-Wtype-limits                                                              \
	-Wdangling-pointer                                                         \
	-Wsizeof-pointer-memaccess                                                 \
	-Wpacked                                                                   \
	-Wrestrict                                                                 \
	-Winit-self                                                                \
	-Wlogical-op                                                               \
	-Wstringop-overflow=4                                                      \
	-Wstringop-truncation

# ── Optimization profiles ────────────────────────────────────────────────────
CFLAGS_COMMON_OPT := -pipe -ffunction-sections -fdata-sections                 \
	-finline-functions -fvisibility=hidden -fstack-protector-strong             \
	-fcf-protection=full -ftrivial-auto-var-init=zero -fno-common              \
	-fstack-clash-protection -g3

CFLAGS_OPT   := $(CFLAGS_COMMON_OPT) -flto -O3 -fno-math-errno  -ffast-math
CFLAGS_NOOPT := $(CFLAGS_COMMON_OPT) -O0

SANITIZE     		:= -fsanitize=address,alignment,undefined -fsanitize-recover=null
SANITIZE_THREAD     := -fsanitize=thread -fsanitize-recover=null

# ── Third-party flags (relaxed — we don't own this code) ─────────────────────
MLX_CFLAGS   := $(MARCH) -O3 -flto -pipe -g3 -I$(MLX_FOLDER) $(LIBS) $(CFLAGS_OPT)

# ── Compiler auto-detection ──────────────────────────────────────────────────
ifeq ($(findstring clang,$(CC_ID)),clang)
  WARNS    := $(WARNS_CLANG)
  LDLTO    := -fuse-ld=lld
else
  CC	   := gcc
  WARNS    := $(WARNS_GCC)
  LDLTO    :=
endif

CFLAGS     := $(MARCH) $(CFLAGS_OPT) $(WARNS)
LDFLAGS    := $(LDLTO) -Wl,--gc-sections -Wl,-O3 -Wl,-z,now $(LIBPATHS) $(LIBS)
# ── Sources ───────────────────────────────────────────────────────────────────
SRCS_PARSER := \
	src/rt_parser/rt_parser.c \
	src/rt_parser/rt_parse_color.c \
	src/rt_parser/rt_parse_coords.c \
	src/rt_parser/rt_parse_sphere.c \
	src/rt_parser/rt_parse_plane.c \
	src/rt_parser/rt_parse_camera.c \
	src/rt_parser/rt_parse_cylinder.c \
	src/rt_parser/rt_parse_light.c \
	src/rt_parser/rt_parse_ambient.c \
	src/rt_parser/rt_init_aos.c \
	src/rt_parser/rt_aos_to_soa.c \
	src/rt_parser/rt_aos_to_soa_plane.c \
	src/rt_parser/rt_aos_to_soa_cylinder.c \
	src/rt_parser/rt_aos_to_soa_light.c \
	src/rt_parser/rt_aos_to_soa_sphere.c \
	src/rt_parser/rt_parse_display_size.c \
	src/rt_parser/rt_parse_path.c \
	src/rt_parser/rt_parse_bmp.c

SRCS_MLX := \
	src/rt_mlx/rt_key_hooks.c \
	src/rt_mlx/rt_mouse_hooks.c \
	src/rt_mlx/rt_killprocess.c

SRCS_POOL := \
	src/rt_pool/rt_threadroutine.c 

SRCS_RENDER := \
	src/rt_render/rt_render.c \
	src/rt_render/rt_render_hotloop.c \
	src/rt_render/rt_camera_ray.c \
	src/rt_render/rt_render_cylinder.c \
	src/rt_render/rt_render_cylinder_caps.c \
	src/rt_render/rt_render_sphere.c \
	src/rt_render/rt_render_frame.c \
	src/rt_render/rt_render_plane.c \
	src/rt_render/rt_shade.c \
	src/rt_render/rt_shade_lights.c

SRCS_LOGGER := \
	src/rt_logger/rt_print_plane.c \
	src/rt_logger/rt_print_cylinder.c \
	src/rt_logger/rt_print_camera.c \
	src/rt_logger/rt_print_sphere.c \
	src/rt_logger/rt_print_light.c \
	src/rt_logger/rt_print_aos.c \
	src/rt_logger/rt_print_soa.c \
	src/rt_logger/rt_errors.c

# ── Third-party: minilibx (compiled in-tree, relaxed warnings) ───────────────
SRCS_THIRDPARTY := \
	minilibx-linux/mlx_clear_window.c \
	minilibx-linux/mlx_destroy_display.c \
	minilibx-linux/mlx_destroy_image.c \
	minilibx-linux/mlx_destroy_window.c \
	minilibx-linux/mlx_expose_hook.c \
	minilibx-linux/mlx_flush_event.c \
	minilibx-linux/mlx_get_color_value.c \
	minilibx-linux/mlx_get_data_addr.c \
	minilibx-linux/mlx_hook.c \
	minilibx-linux/mlx_init.c \
	minilibx-linux/mlx_int_anti_resize_win.c \
	minilibx-linux/mlx_int_do_nothing.c \
	minilibx-linux/mlx_int_get_visual.c \
	minilibx-linux/mlx_int_param_event.c \
	minilibx-linux/mlx_int_set_win_event_mask.c \
	minilibx-linux/mlx_int_str_to_wordtab.c \
	minilibx-linux/mlx_int_wait_first_expose.c \
	minilibx-linux/mlx_key_hook.c \
	minilibx-linux/mlx_loop.c \
	minilibx-linux/mlx_loop_hook.c \
	minilibx-linux/mlx_mouse.c \
	minilibx-linux/mlx_mouse_hook.c \
	minilibx-linux/mlx_new_image.c \
	minilibx-linux/mlx_new_window.c \
	minilibx-linux/mlx_pixel_put.c \
	minilibx-linux/mlx_put_image_to_window.c \
	minilibx-linux/mlx_rgb.c \
	minilibx-linux/mlx_screen_size.c \
	minilibx-linux/mlx_set_font.c \
	minilibx-linux/mlx_string_put.c \
	minilibx-linux/mlx_xpm.c

MINIRT_SRCS := $(SRCS_RENDER) $(SRCS_PARSER) $(SRCS_MLX) $(SRCS_LOGGER) $(SRCS_POOL)
MLX_OBJS := $(patsubst minilibx-linux/%.c,$(OBJDIR)/thirdparty/%.o,$(SRCS_THIRDPARTY))

# ── Aggregate ─────────────────────────────────────────────────────────────────
MODULES     := PARSER MLX RENDER LOGGER POOL
SRCS        := src/main.c $(foreach m,$(MODULES),$(SRCS_$(m)))
OBJS        := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))
ALL_OBJS    := $(OBJS) $(MLX_OBJS)
COMMON_OBJS := $(filter-out $(OBJDIR)/main.o,$(ALL_OBJS))

# ── Tests ─────────────────────────────────────────────────────────────────────
TEST_SRCS := \
	tests/rt_parse_coord_test.c \
	tests/rt_parse_color_test.c \
	tests/rt_parse_sphere.c \
	tests/rt_parse_light.c \
	tests/rt_parse_cylinder.c \
	tests/rt_parse_camera.c \
	tests/rt_parse_ambient.c \
	tests/rt_parse_plane.c
TEST_OBJS := $(patsubst tests/%.c,$(OBJDIR)/tests/%.o,$(TEST_SRCS))
TEST_BINS := $(patsubst tests/%.c,$(OBJDIR)/tests/%,$(TEST_SRCS))

# ═════════════════════════════════════════════════════════════════════════════
#  Targets
# ═════════════════════════════════════════════════════════════════════════════

all: $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_FOLDER) CFLAGS="$(CFLAGS)"

# ── Pattern rules ────────────────────────────────────────────────────────────
# Our code: full warnings
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Third-party mlx: relaxed warnings — we don't own this code
$(OBJDIR)/thirdparty/%.o: minilibx-linux/%.c
	@mkdir -p $(dir $@)
	$(CC) $(MLX_CFLAGS) -c $< -o $@

$(NAME): $(ALL_OBJS) libft
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LDFLAGS) -Wl,-s -o $@

# ── Convenience ──────────────────────────────────────────────────────────────
sanitize: $(ALL_OBJS) libft
	$(CC) $(CFLAGS) $(SANITIZE) $(ALL_OBJS) $(LDFLAGS) -o miniRTSan

sanitize_thread: $(ALL_OBJS) libft
	$(CC) $(CFLAGS) $(SANITIZE_THREAD) $(ALL_OBJS) $(LDFLAGS) -o miniRTSanT

debug: libft
	@$(MAKE) $(OBJS) CFLAGS="$(MARCH) $(CFLAGS_NOOPT) $(WARNS)"
	@$(MAKE) $(MLX_OBJS)
	@$(MAKE) re -C $(LIBFT_FOLDER) CFLAGS="$(MARCH) $(CFLAGS_NOOPT) $(WARNS)"
	$(CC) $(CFLAGS_NOOPT) $(ALL_OBJS) $(LDFLAGS) -o miniRTdbg

base:
	$(MAKE) fclean all CFLAGS="$(CFLAGS_NOOPT) $(WARNS)"

clean:
	@$(MAKE) clean -C $(LIBFT_FOLDER)
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_FOLDER)
	@rm -f $(NAME) miniRTSan miniRTdbg

re: fclean all

# ── Static analysis (our code only, not third-party) ────────────────────────
static_analysis:
	$(SCANNER) $(CC_CLANG) $(WARNS_CLANG) $(CFLAGS_OPT) $(MARCH) $(INCLUDES) \
		-Xclang -analyzer-output=text --analyze $(MINIRT_SRCS)
	$(SCANNER) $(CC_CLANG) $(WARNS_CLANG) $(CFLAGS_OPT) $(INCLUDES) \
		-Xclang -analyzer-output=text --analyze  $(MINIRT_SRCS)
	$(CC_GCC) $(CFLAGS_OPT) $(MARCH) $(INCLUDES) \
		-fanalyzer $(MINIRT_SRCS) -c && rm -f *.o
	$(CC_GCC) $(CFLAGS_OPT) $(INCLUDES) \
		-fanalyzer $(MINIRT_SRCS) -c && rm -f *.o
	norminette src/ include/ tests/ $(LIBFT_FOLDER)
# GCC has no warns bc it fails in the mlx header
# ── Tests ────────────────────────────────────────────────────────────────────
$(OBJDIR)/tests/%.o: tests/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/tests/%: $(OBJDIR)/tests/%.o $(COMMON_OBJS) libft
	$(CC) $(CFLAGS) $(SANITIZE) $< $(COMMON_OBJS) $(LDFLAGS) -o $@

test: $(TEST_BINS)
	@for bin in $(TEST_BINS); do \
		./$$bin || exit 1; \
	done

analyze: static_analysis
	@$(MAKE) analyze -C $(LIBFT_FOLDER)

.PHONY: all clean fclean re libft base test static_analysis analyze sanitize debug
MAKEFLAGS += --no-print-directory
