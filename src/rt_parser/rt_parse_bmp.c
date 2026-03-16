/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:56:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 23:28:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_bmp.h"
#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "bmi.h"
#include "map.h"
#include "io.h"
#define RT_PATH_PREFIX "TXR="

__attribute__((__nonnull__(4), __always_inline__))
static inline void	bmp_decode(t_BMPHeader bmp, t_DIBHeader dib,
	t_file file, t_RTTexture *tx)
{
	const t_u32	*src;
	size_t		y;
	size_t		x;

	y = 0;
	while (y < tx->height)
	{
		src = (const t_u32 *)((t_u8 *)file.content + bmp.data_offst)
			+ ((dib.height > 0) * (tx->height - 1 - y)
				| (dib.height < 0) * y) * tx->width;
		x = 0;
		while (x < tx->width)
		{
			tx->data[y * tx->width + x] = (src[x] & 0xFF00FF00u)
				| ((src[x] & 0xFFu) << 16)
				| ((src[x] >> 16) & 0xFFu);
			x++;
		}
		y++;
	}
}

__attribute__((__always_inline__, const))
static inline t_taggedresult	enforce_bmp(t_BMPHeader bmp, t_DIBHeader dib,
	t_file f, size_t row_size)
{
	if (bmp.id != 0x4D42)
		rt_error("Error\n.bmp file is not a BMP file\n");
	else if (f.size < bmp.data_offst)
		rt_error("Error\n.bmp file is corrupted\n");
	else if (dib.bpp != 32)
		rt_error("Error\n.bmp file is not RGBA\n");
	else if (dib.compression != 0 && dib.compression != 3)
		rt_error("Error\n.bmp file is compressed\n");
	else if (f.size - bmp.data_offst < (size_t)abs(dib.height) * row_size)
		rt_error("Error\n.bmp file is not big enough");
	else
		return (OK);
	return (KO);
	
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_RTTexture	*decode_bmp(t_RTContext *ctx, t_file f)
{
	t_BMPHeader	bmp;
	t_DIBHeader	dib;
	t_u32a		row_size;
	t_RTTexture	*tx;
	size_t		npix;

	if (f.size <= sizeof(bmp) + sizeof(dib))
		return ((void *)BMP_ERROR);
	bmp = *(const t_BMPHeader * restrict const)f.content;
	dib = *(const t_DIBHeader * restrict const)(f.content + sizeof(bmp));
	row_size = ((t_u32a)((dib.width * dib.bpp) >> 3) + 3) & ~3u;
	if (enforce_bmp(bmp, dib, f, row_size) == KO)
		return ((void *)BMP_ERROR);
	npix = (size_t)dib.width * (size_t)abs(dib.height);
	tx = ft_arena_alloc(&ctx->rt_arena,
			(npix << 2) + sizeof(t_RTTexture), 64);
	if (!tx)
		return ((void *)BMP_ERROR);
	tx->height = abs(dib.height);
	tx->width = dib.width;
	bmp_decode(bmp, dib, f, tx);
	return (tx);
}

__attribute__((__nonnull__(1)))
t_RTTexture	*rt_parse_bmp(t_RTContext *ctx, t_token tok)
{
	t_file				file;
	char				*fname;
	t_RTTexture			*tx;

	if (tok.len <= sizeof(RT_PATH_PREFIX)
		|| ft_to_be32(*(t_u32 *)tok.mem) != ft_to_be32(0x3D525854))
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
	tx = decode_bmp(ctx, file);
	if (tx)
		ft_map_insert(&ctx->loaded_textures, (t_u8 *)fname, tok.len, (void *)tx);
	ft_close_file(&file);
	return (tx);
}
