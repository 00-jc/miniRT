/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:38:59 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:58:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"

__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_light(t_tokenizer *t, t_vec *light_vec)
{
	t_coord_result	coords;
	t_double_res	brightness;
	t_color_result	color;
	t_RTLight		light;

	coords = rt_parse_coords(t);
	if (coords.res == KO)
		return (KO);
	brightness = rt_parse_double(t);
	if (brightness.res == KO)
		return (KO);
	if (((brightness.d - 1.0) > 0) | (brightness.d < 0))
		return (rt_error(NBRI), KO);
	color = rt_parse_color(t);
	if (color.res == KO)
		return (KO);
	light = (t_RTLight){.coords = coords.coord, .brightness = brightness.d,
		.color = color.color};
	return (ft_vec_push_back(light_vec, (void *){&light}, sizeof(light)));
}
