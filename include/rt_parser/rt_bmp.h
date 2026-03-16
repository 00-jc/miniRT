/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:29:32 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 22:36:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_BMP_H
# define RT_BMP_H
# include "types.h"

# define BMP_ERROR 1

typedef struct s_BmpHeader
{
	t_u16	id;
	t_u32	size_in_bytes;
	t_u32	_;
	t_u32	data_offst;
} __attribute__((packed, aligned(1)))	t_BMPHeader;

typedef struct s_dib
{
	t_u32		header_size;
	int32_t		width;
	int32_t		height;
	t_u16		planes;
	t_u16		bpp;
	t_u32		compression;
	t_u32		image_size;
	int32_t		x_ppm;
	int32_t		y_ppm;
	t_u32		colors_used;
	t_u32		colors_important;
} __attribute__((packed, aligned(1)))	t_DIBHeader;

typedef struct s_RTTexture
{
	size_t		width;
	size_t		height;
	t_u32a		data[];
}	t_RTTexture;

#endif
