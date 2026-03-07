/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:03:55 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 21:04:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_camera(t_RTCamera *camera)
{
	ft_printf("Object: Camera\n");
	ft_printf("\tcoords: %f, %f, %f\n", camera->coords,
		camera->coords, camera->coords);
	ft_printf("\taxis: %f, %f, %f\n", camera->axis,
		camera->axis, camera->axis);
	ft_printf("\tfov: %d\n", camera->fov);
	ft_printf("\tinitialization: %d\n", camera->is_init);
}
