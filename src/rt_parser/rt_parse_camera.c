/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:56:13 by asoria            #+#    #+#             */
/*   Updated: 2026/03/15 15:45:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"

__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_camera(t_tokenizer *t, t_RTCamera *cam)
{
	t_coord_result	coords;
	t_coord_result	vector;
	t_unsigned_res	fov;

	if (cam->is_init)
		return (rt_error(REDEF, "'Camera'"), KO);
	coords = rt_parse_coords(t);
	if (coords.res == KO)
		return (KO);
	vector = rt_parse_coords(t);
	if (vector.res == KO)
		return (KO);
	fov = rt_parse_usigned(t);
	if (fov.res == KO)
		return (KO);
	if (fov.u > 180)
		return (rt_error(OOR, fov.u, 0ULL, 180ULL), KO);
	*cam = (t_RTCamera){.coords = coords.coord, .axis = vector.coord,
		.fov = (t_u8)fov.u, .is_init = 1};
	return (OK);
}
