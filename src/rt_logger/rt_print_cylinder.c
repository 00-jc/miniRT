/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:44:11 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 21:25:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_cylinder(t_RTCylinder *cylinder)
{
	ft_printf("Object: Cylinder\n");
	ft_printf("\tcoords: %f, %f, %f\n", cylinder->coords,
		cylinder->coords, cylinder->coords);
	ft_printf("\taxis: %f, %f, %f\n", cylinder->axis,
		cylinder->axis, cylinder->axis);
	ft_printf("\twidth/height: %f, %f\n", cylinder->wh.x, cylinder->wh.y);
	ft_printf("\tcolor: %x\n", cylinder->color);
}
