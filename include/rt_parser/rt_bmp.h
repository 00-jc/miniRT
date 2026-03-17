/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:29:32 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 18:06:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_BMP_H
# define RT_BMP_H
# include "types.h"

# define RT_PATH_PREFIX "MAP="
# define RT_COLOR_PREFIX "TXT="
# define BMP_ERROR 1

typedef struct s_RTTexture
{
	size_t		width;
	size_t		height;
	t_u8		data[];
}	t_RTTexture;

typedef struct s_RTColortx
{
	size_t		width;
	size_t		height;
	t_u32		data[];
}	t_RTColortx;

#endif
