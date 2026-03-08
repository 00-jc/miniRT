/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:01:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/08 02:42:13 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_sphere(t_RTSphere *sphere)
{
	ft_printf("Object: Sphere\n");
	ft_printf("\tcoords: %f, %f, %f\n", sphere->coords.x,
		sphere->coords.y, sphere->coords.z);
	ft_printf("\tdiameter: %f\n", sphere->diameter);
	ft_printf("\tcolor: %x\n", sphere->color);
}
