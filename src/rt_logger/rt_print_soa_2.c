/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_soa_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:43:46 by asoria            #+#    #+#             */
/*   Updated: 2026/03/17 20:06:13 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_cone(t_RTScene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->rt_cone_buffer.size)
	{
		ft_printf("Cone %d:\n\tcoords: %f %f %f\n\taxis: %f\n",
			i, scene->rt_cone_buffer.coords[i].x,
			scene->rt_cone_buffer.coords[i].y,
			scene->rt_cone_buffer.coords[i].z,
			scene->rt_cone_buffer.axis[i].x,
			scene->rt_cone_buffer.axis[i].y,
			scene->rt_cone_buffer.axis[i].z);
		ft_printf("\tdiameter/height: %f %f\n\tcolor: %x\n",
			scene->rt_cone_buffer.wh[i].x,
			scene->rt_cone_buffer.wh[i].y,
			scene->rt_cone_buffer.color[i]);
		i++;
	}
}
