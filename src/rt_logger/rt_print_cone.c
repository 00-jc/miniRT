/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>        +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by asoria            #+#    #+#             */
/*   Updated: 2026/03/17 22:27:28 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_cone(t_RTCone *cone)
{
	ft_printf("Object: Cone\n");
	ft_printf("\tcoords: %f, %f, %f\n", cone->coords.x,
		cone->coords.y, cone->coords.z);
	ft_printf("\taxis: %f, %f, %f\n", cone->axis.x,
		cone->axis.y, cone->axis.z);
	ft_printf("\tdiameter/height: %f, %f\n", cone->wh.x, cone->wh.y);
	ft_printf("\tcolor: %x\n", cone->color);
}
