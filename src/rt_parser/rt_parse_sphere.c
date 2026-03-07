/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 01:11:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 01:37:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"

__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_sphere(t_tokenizer *t, t_vec *sphere_vec)
{
	t_coord_result	coords;
	t_color_result	color;
	t_double_res	diameter;
	t_RTSphere		sphere;

	coords = rt_parse_coords(t);
	if (coords.res == KO)
		return (KO);
	diameter = rt_parse_double(t);
	if (diameter.res == KO)
		return (KO);
	if (diameter.d < 0.0)
		return (rt_error(NDIAM), KO);
	color = rt_parse_color(t);
	if (color.res == KO)
		return (KO);
	sphere = (t_RTSphere){.coords = coords.coord,
		.diameter = diameter.d, .color = color.color};
	return (ft_vec_push_back(sphere_vec, (void *){&sphere},
		sizeof(t_RTSphere)));
}
