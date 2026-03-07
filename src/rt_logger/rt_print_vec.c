/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:19:28 by asoria            #+#    #+#             */
/*   Updated: 2026/03/07 21:22:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_logger/rt_printer.h"
#include "vec.h"

__attribute__((__always_inline__))
inline void	rt_print_aos_sphere(t_vec vec)
{
	size_t		i;
	size_t		len;
	t_RTSphere	*sphere;

	len = ft_vec_len(&vec, sizeof(t_RTSphere));
	i = 0;
	while (i < len)
	{
		sphere = (t_RTSphere *)ft_vec_get(&vec, i, sizeof(*sphere));
		rt_print_sphere(sphere);
		i++;
	}
}

__attribute__((__always_inline__))
inline void	rt_print_aos_light(t_vec vec)
{
	size_t		i;
	size_t		len;
	t_RTLight	*light;

	len = ft_vec_len(&vec, sizeof(t_RTLight));
	i = 0;
	while (i < len)
	{
		light = (t_RTLight *)ft_vec_get(&vec, i, sizeof(*light));
		rt_print_light(light);
		i++;
	}
}

__attribute__((__always_inline__))
inline void	rt_print_aos_plane(t_vec vec)
{
	size_t		i;
	size_t		len;
	t_RTPlane	*plane;

	len = ft_vec_len(&vec, sizeof(t_RTPlane));
	i = 0;
	while (i < len)
	{
		plane = (t_RTPlane *)ft_vec_get(&vec, i, sizeof(*plane));
		rt_print_plane(plane);
		i++;
	}
}

__attribute__((__always_inline__))
inline void	rt_print_aos_cylinder(t_vec vec)
{
	size_t			i;
	size_t			len;
	t_RTCylinder	*cylinder;

	len = ft_vec_len(&vec, sizeof(t_RTCylinder));
	i = 0;
	while (i < len)
	{
		cylinder = (t_RTCylinder *)ft_vec_get(&vec, i, sizeof(*cylinder));
		rt_print_cylinder(cylinder);
		i++;
	}
}

/*
	In the AOS:

	0 = t_Sphere
	1 = t_RTLight
	2 = t_RTPlane
	3 = t_RTCylinder
*/
__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	rt_print_aos(t_vec vec[4], t_RTScene *scene)
{
	rt_print_aos_sphere(vec[0]);
	rt_print_aos_light(vec[1]);
	rt_print_aos_plane(vec[2]);
	rt_print_aos_cylinder(vec[3]);
	rt_print_ambient(&scene->rt_ambient);
	rt_print_camera(&scene->rt_camera);
}
