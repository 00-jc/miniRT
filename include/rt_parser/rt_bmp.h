/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:29:32 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 02:19:51 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_BMP_H
# define RT_BMP_H
# include "types.h"

# define BMP_ERROR 1

typedef struct s_RTTexture
{
	size_t		width;
	size_t		height;
	t_u8		data[];
}	t_RTTexture;

#endif
