/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:44:11 by asoria            #+#    #+#             */
/*   Updated: 2026/03/08 02:40:50 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_cylinder(t_RTCylinder *cylinder)
{
	ft_printf("Object: Cylinder\n");
	ft_printf("\tcoords: %f, %f, %f\n", cylinder->coords.x,
		cylinder->coords.y, cylinder->coords.z);
	ft_printf("\taxis: %f, %f, %f\n", cylinder->axis.x,
		cylinder->axis.y, cylinder->axis.z);
	ft_printf("\twidth/height: %f, %f\n", cylinder->wh.x, cylinder->wh.y);
	ft_printf("\tcolor: %x\n", cylinder->color);
}
