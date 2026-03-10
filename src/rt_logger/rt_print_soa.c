/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_soa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 04:00:57 by asoria            #+#    #+#             */
/*   Updated: 2026/03/10 02:14:15 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_logger/rt_printer.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_sphere(t_RTSphereBuffer *sp)
{
	size_t	i = 0;

	while (i < sp->size)
	{
		ft_printf("Sphere %d:\n\tcoords: %d %d %d\n\tdiameter: %d\n\tcolor: %h",
				i, sp->coords->x, sp->coords->y, sp->coords->z, sp->diameter,
				sp->color);
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_light(t_RTLightBuffer *l)
{
	(void)l;
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_plane(t_RTPlaneBuffer *pl)
{
	(void)pl;
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_cylinder(t_RTCylinderBuffer *cy)
{
	(void)cy;
}

__attribute__((__always_inline__, nonnull(1)))
inline void	rt_print_soa(t_RTScene *scene)
{
	ft_printf("Ambient Light:\n\tbrightness: %f\n\tcolor: %x\n\tis_init: %d\n",
		scene->rt_ambient.brightness, scene->rt_ambient.color,
		scene->rt_ambient.is_init);
	ft_printf("Camera:\n\tcoords: %f %f %f\n\tfov: %d\n",
		scene->rt_camera.coords.x, scene->rt_camera.coords.y,
		scene->rt_camera.coords.z, scene->rt_camera.fov);
	ft_printf("\taxis: %f %f %f\n\tis_init: %d\n",
		scene->rt_camera.axis.x, scene->rt_camera.axis.y,
		scene->rt_camera.axis.z, scene->rt_camera.is_init);
	rt_print_soa_sphere(&scene->rt_sphere_buffer);
	rt_print_soa_light(&scene->rt_light_buffer);
	rt_print_soa_plane(&scene->rt_plane_buffer);
	rt_print_soa_cylinder(&scene->rt_cylinder_buffer);
}
