/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:05:52 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 20:59:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_plane(t_RTPlane *plane)
{
	ft_printf("Object: Plane\n");
	ft_printf("\tcoords: %f, %f, %f\n", plane->coords.x,
		plane->coords.y, plane->coords.z);
	ft_printf("\taxis: %f, %f, %f\n", plane->axis.x,
		plane->axis.y, plane->axis.z);
	ft_printf("\tcolor: %x\n", plane->color);
}
