/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect_nonuniq.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:03:04 by asoria            #+#    #+#             */
/*   Updated: 2026/03/12 21:36:27 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__attribute__((__always_inline__))
inline double	rt_intersect_sphere(t_RTRay ray, size_t i,
		t_RTSphereBuffer *buf)
{
	t_3dcoords	oc;
	double		b;
	double		c;
	double		disc;
	double		radius;

	radius = buf->diameter[i] * 0.5;
	oc = ft_3dsub(ray.origin, buf->coords[i]);
	b = 2.0 * ft_3ddot(oc, ray.dir);
	c = ft_3ddot(oc, oc) - radius * radius;
	disc = b * b - 4.0 * c;
	if (disc < 0)
		return (-1);
	disc = ft_dsqrt(disc);
	if ((-b - disc) * 0.5 > 0)
		return ((-b - disc) * 0.5);
	return ((-b + disc) * 0.5);
}
