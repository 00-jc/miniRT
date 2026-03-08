/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:03:55 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/08 02:40:09 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_print_camera(t_RTCamera *camera)
{
	ft_printf("Object: Camera\n");
	ft_printf("\tcoords: %f, %f, %f\n", camera->coords.x,
		camera->coords.y, camera->coords.z);
	ft_printf("\taxis: %f, %f, %f\n", camera->axis.x,
		camera->axis.y, camera->axis.z);
	ft_printf("\tfov: %d\n", camera->fov);
	ft_printf("\tinitialization: %d\n", camera->is_init);
}
