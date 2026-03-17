/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:56:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 20:17:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_bmp.h"
#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "bmi.h"
#include "map.h"
#include "io.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline t_RTTexture	*rt__decode(t_RTContext *ctx, t_file file)
{
	t_u64		width;
	t_u64		height;
	t_RTTexture	*tx;

	if (file.size <= (sizeof(t_u64) << 1))
		return ((void *)BMP_ERROR);
	width = ((t_blk64r)file.content)[0];
	height = ((t_blk64r)file.content)[1];
	if ((width & (width - 1)) | (height & (height - 1)))
		return (rt_error("Error\nImage size must be power of 2"),
			(void *)BMP_ERROR);
	tx = ft_arena_alloc(&ctx->rt_arena, sizeof(t_RTTexture)
			+ width * height, 64);
	if (!tx)
		return ((void *)BMP_ERROR);
	ft_memcpy(tx->data, file.content + (sizeof(t_u64) << 1),
		width * height);
	tx->width = width;
	tx->height = height;
	return (tx);
}

__attribute__((__nonnull__(1)))
t_RTTexture	*rt_parse_bmp(t_RTContext *ctx, t_token tok)
{
	t_file				file;
	char				*fname;
	t_RTTexture			*tx;

	if (tok.len <= sizeof(RT_PATH_PREFIX)
		|| ft_to_be32(*(t_u32 *)tok.mem) != ft_to_be32(0x3D50414D))
		return (NULL);
	tok.len -= sizeof(RT_PATH_PREFIX) - 1;
	tok.mem += sizeof(RT_PATH_PREFIX) - 1;
	tx = ft_map_lookup(&ctx->loaded_textures, tok.mem, tok.len);
	if (tx)
		return (tx);
	fname = ft_arena_alloc(&ctx->rt_arena, tok.len + 1, 4);
	if (!fname)
		return ((void *)BMP_ERROR);
	ft_memcpy(fname, tok.mem, tok.len);
	fname[tok.len] = 0;
	file = ft_read_file(fname);
	if (!file.content)
		return (rt_error(NFOUND), (void *)BMP_ERROR);
	tx = rt__decode(ctx, file);
	if ((t_uptr)tx != BMP_ERROR)
		ft_map_insert(&ctx->loaded_textures, (t_u8 *)fname, tok.len,
			(void *)tx);
	return (ft_close_file(&file), tx);
}
