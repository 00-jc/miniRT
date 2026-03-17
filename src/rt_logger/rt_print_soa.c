/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_soa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 04:00:57 by asoria            #+#    #+#             */
/*   Updated: 2026/03/17 19:45:21 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_logger/rt_printer.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_sphere(t_RTScene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->rt_sphere_buffer.size)
	{
		ft_printf(
			"Sphere %d:\n\tcoords: %f %f %f\n\tdiameter: %f\n\tcolor: %x\n",
			i, scene->rt_sphere_buffer.coords[i].x,
			scene->rt_sphere_buffer.coords[i].y,
			scene->rt_sphere_buffer.coords[i].z,
			scene->rt_sphere_buffer.diameter[i],
			scene->rt_sphere_buffer.color[i]);
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_light(t_RTScene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->rt_light_buffer.size)
	{
		ft_printf(
			"Light %d:\n\tcoords: %f %f %f\n\tbrightness: %f\n\tcolor: %x\n",
			i, scene->rt_light_buffer.coords[i].x,
			scene->rt_light_buffer.coords[i].y,
			scene->rt_light_buffer.coords[i].z,
			scene->rt_light_buffer.brightness[i],
			scene->rt_light_buffer.color[i]);
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_plane(t_RTScene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->rt_plane_buffer.size)
	{
		ft_printf(
			"Plane %d:\n\tcoords: %f %f %f\n\taxis: %f\n\tcolor: %x\n",
			i, scene->rt_plane_buffer.coords[i].x,
			scene->rt_plane_buffer.coords[i].y,
			scene->rt_plane_buffer.coords[i].z,
			scene->rt_plane_buffer.axis[i].x,
			scene->rt_plane_buffer.axis[i].y,
			scene->rt_plane_buffer.axis[i].z,
			scene->rt_plane_buffer.color[i]);
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_print_soa_cylinder(t_RTScene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->rt_cylinder_buffer.size)
	{
		ft_printf("Cylinder %d:\n\tcoords: %f %f %f\n\taxis: %f\n",
			i, scene->rt_cylinder_buffer.coords[i].x,
			scene->rt_cylinder_buffer.coords[i].y,
			scene->rt_cylinder_buffer.coords[i].z,
			scene->rt_cylinder_buffer.axis[i].x,
			scene->rt_cylinder_buffer.axis[i].y,
			scene->rt_cylinder_buffer.axis[i].z);
		ft_printf("\twidth/height: %f %f\n\tcolor: %x\n",
			scene->rt_cylinder_buffer.wh[i].x,
			scene->rt_cylinder_buffer.wh[i].y,
			scene->rt_cylinder_buffer.color[i]);
		i++;
	}
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
	rt_print_soa_sphere(scene);
	rt_print_soa_light(scene);
	rt_print_soa_plane(scene);
	rt_print_soa_cylinder(scene);
	rt_print_soa_cone(scene);
}
