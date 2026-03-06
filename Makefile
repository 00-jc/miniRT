# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 17:40:40 by jaicastr          #+#    #+#              #
#    Updated: 2026/03/06 03:06:44 by jaicastr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	miniRT
CC				:=	clang
OBJDIR			:=	build
LIBFT_FOLDER	:=	libft
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
CFLAGS_DEBUG	:=	-flto -O0 -pipe -ffunction-sections -fdata-sections -finline-functions \
					-fvisibility=hidden -fstack-protector-strong -fcf-protection=full -ftrivial-auto-var-init=zero \
					-fno-common -fstack-clash-protection -g3
SANITIZE		:= 	-fsanitize=address,alignment,undefined -fsanitize-recover=null
CFLAGS			:=	$(MARCH) $(CFLAGS_BASE) $(WARNS)
SRCS			:=	src/main.c\
					src/parser/parser.c\
					src/parser/parse_color.c\
					src/parser/parse_coords.c
OBJS			:=	$(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_FOLDER)

mlx:
	@$(MAKE) -C $(MLX_FOLDER)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -g3 -c $< -o $@

$(NAME): $(OBJS) libft mlx
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

sanitize: $(OBJS) libft mlx
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o miniRTSan $(SANITIZE)

debug: $(OBJS) libft mlx
	@$(MAKE) re -C $(LIBFT_FOLDER) CFLAGS="$(MARCH) $(CFLAGS_DEBUG) $(WARNS_CLANG)"
	@$(CC) $(CFLAGS_DEBUG) $(OBJS) $(LDFLAGS) -o miniRTdbg

clean:
	@$(MAKE) clean -C $(LIBFT_FOLDER)
	@$(MAKE) clean -C $(MLX_FOLDER)
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_FOLDER)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft mlx
MAKEFLAGS += --no-print-directory
