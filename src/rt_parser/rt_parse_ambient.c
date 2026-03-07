/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:56:13 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 04:30:06 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"

__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_ambient(t_tokenizer *t, t_RTAmbientLight *ambient,
		t_u8 init)
{
	t_double_res	d;
	t_color_result	color;

	if (init)
		return (rt_error(REDEF, "'Ambient Light'"), KO);
	d = rt_parse_double(t);
	if (d.res == KO)
		return (KO);
	if ((d.d - 1.0) > 0 || d.d < 0)
		return (rt_error(OORD, d.d, 0.0, 1.0), KO);
	color = rt_parse_color(t);
	if (color.res == KO)
		return (KO);
	*ambient = (t_RTAmbientLight){.color = color.color, .brightness = d.d};
	return (OK);
}
